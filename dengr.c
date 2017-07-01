#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "dengr.h"


#ifdef __cplusplus
extern "C"{
#endif

dengr_nanometre_t dengr_mm_to_nm(dengr_millimetre_t mm) {
    return (dengr_nanometre_t)mm * 1000000;
}

static dengr_nanometre_t dengr_get_cd_track_length(dengr_cd_brief_spec_t brief);

static size_t dengr_get_cd_capacity(dengr_cd_brief_spec_t brief);

dengr_cd_full_spec_t dengr_brief_spec_to_full_spec(
    dengr_cd_brief_spec_t brief
) {
    return (dengr_cd_full_spec_t) {
        .track_pitch = brief.track_pitch,
        .track_length = dengr_get_cd_track_length(brief),
        .inner_radius = brief.inner_radius,
        .outer_radius = brief.outer_radius,
        .capacity = dengr_get_cd_capacity(brief),
    };
}

static dengr_nanometre_t dengr_get_cd_track_length(
    dengr_cd_brief_spec_t brief
) {
    return (dengr_nanometre_t)(
        (
            M_PI * (
                powl(brief.outer_radius, 2.0l) -
                powl(brief.inner_radius, 2.0l)
            )
        ) / brief.track_pitch
    );
}

static size_t dengr_get_cd_capacity(dengr_cd_brief_spec_t brief) {
    return brief.sector_count * DENGR_CDDA_SECTOR_SIZE;
}

// private structure for passing context data to co-ord handler callback
struct dengr_co_ord_handler_data_t {
    dengr_cd_full_spec_t* spec;
    dengr_bitmap_t* image;
    size_t sector_count;
    dengr_audio_sector_t sector;
    void(* write_sector_callback)(
        size_t sector_index,
        dengr_audio_sector_t sector,
        void* write_sector_data
    );
    void* write_sector_data;
};

/*
 * for a given full CD spec, a maximum number of points to plot (no limit set if
 * 0), a pointer to custom data of a user-defined type and a callback to a
 * function which receives each co-ordinate, index of point found and the custom
 * data pointer as arguments, find all the x-y co-ordinates of the CD and call
 * the given callback with each x-y co-ordinate found (and the user data too)
 */
static void dengr_trace_cd_spiral(
    dengr_cd_full_spec_t spec,
    size_t max_points,
    void(* callback)(
        dengr_co_ordinate_t co_ordinate,
        size_t index,
        void* user_data
    ),
    void* user_data
);

// handles the conversion of co-ordinates into cd audio data
static void dengr_co_ord_handler(
    dengr_co_ordinate_t co_ordinate,
    size_t index,
    void* user_data
);

void dengr_plot_image_to_audio(
    dengr_cd_full_spec_t spec,
    dengr_bitmap_t image,
    void(* write_sector)(
        size_t sector_index,
        dengr_audio_sector_t sector,
        void* write_sector_data
    ),
    void* write_sector_data
) {
    // we must be given a callback
    assert(write_sector != NULL);
    // build context data for callback
    struct dengr_co_ord_handler_data_t user_data = {
        .spec = &spec,
        .image = &image,
        .sector_count = 0,
        .write_sector_callback = write_sector,
        .write_sector_data = write_sector_data,
    };
    /*
     * trace the spiral and pass a callback which will handle the generation of
     * each sector
     */
    dengr_trace_cd_spiral(spec, 0, dengr_co_ord_handler, (void*)&user_data);
}

static dengr_co_ordinate_t dengr_polar_to_cartesian(
    long double radius, long double angle
);

static void dengr_trace_cd_spiral(
    dengr_cd_full_spec_t spec,
    size_t max_points,
    void(* callback)(
        dengr_co_ordinate_t co_ordinate,
        size_t index,
        void* user_data
    ),
    void* user_data
) {
    // we must be given a callback
    assert(callback != NULL);
    // work out how many points we are asked to plot
    size_t point_count = spec.capacity;
    if(max_points != 0 && max_points < spec.capacity) {
        point_count = max_points;
    }
    // store inner radius now as we'll make frequent use of it
    long double inner_radius = (long double)spec.inner_radius;
    // store pitch for the same reason
    long double pitch = (long double)spec.track_pitch;
    // this is the size of the angle, measured in 'turns'
    long double angle = 0.0l;
    // this is the radius of the spiral, and keeps increasing with angle
    long double radius = inner_radius;
    // the first point is a one-off
    callback(dengr_polar_to_cartesian(radius, angle), 0, user_data);
    /*
     * the 'step' is the angular increase we need to make to keep a constant
     * distance between each point of the spiral.
     */
    long double step = (long double)spec.track_length / spec.capacity;
    // this is the main loop of the point-plotting algorithm
    for(size_t i = 1; i < point_count; i++) {
        /*
         * update angle (based on a proportional increase of step to keep equal
         * distance)
         */
        angle += step / (radius * 2 * M_PI);
        // This bit is the magic of Archimedes' spiral equation :)
        // r = a + b * theta
        radius = inner_radius + pitch * angle;
        // give the x-y co-ordinate to the callback
        callback(dengr_polar_to_cartesian(radius, angle), i, user_data);
    }
    // end
    return;
}

static dengr_co_ordinate_t dengr_polar_to_cartesian(
    long double radius, long double angle
) {
    return (dengr_co_ordinate_t){
        .x = (dengr_nanometre_t)(radius * cosl(angle * 2.0l * M_PI)),
        .y = (dengr_nanometre_t)(radius * sinl(angle * 2.0l * M_PI)),
    };
}

/*
 * Converts a black or white pixel value into a byte which, once subject to
 * eight-to-fourteen modulation would appear 'dark' or 'light' respectively
 * (owing to the respective bit patterns used for either EFM code).
 */
static uint8_t dengr_get_efm_byte_for_pixel(dengr_pixel_t pixel);

/*
 * for a given full CD spec, x-y co-ordinates of a point on a CD pertaining to
 * that CD spec and a bitmap image, find the image pixel which is located at the
 * given x-y co-ordinates if the image was mapped at a 1:1 ratio to the CD
 * program area
 */
static dengr_pixel_t dengr_get_pixel_at_position(
    dengr_cd_full_spec_t spec,
    dengr_co_ordinate_t position,
    dengr_bitmap_t image
);

/*
 * Reverses CIRC-encoding and the 'scrambling' systems defined in ECMA-130.
 * These operate on the whole sector at once. Reversing them means that the data
 * output from this function, if encoded with 'scrambling' and CIRC would yield
 * the data input to this function.
 */
static dengr_audio_sector_t dengr_reverse_sector_encoding(
    dengr_audio_sector_t sector
);

static void dengr_co_ord_handler(
    dengr_co_ordinate_t co_ordinate,
    size_t index,
    void* user_data
) {
    // cast user data back to our struct type and dereference
    struct dengr_co_ord_handler_data_t* context = (
        (struct dengr_co_ord_handler_data_t*)user_data
    );
    const size_t sector_index = index % DENGR_CDDA_SECTOR_SIZE;
    // retrieve the image pixel at given co-ordinate and write to sector buffer
    context->sector.data[sector_index] = dengr_get_efm_byte_for_pixel(
        dengr_get_pixel_at_position(
            *context->spec,
            co_ordinate,
            *context->image
        )
    );
    /*
     * if this is the last byte of the sector, then we can now run the remainder
     * of processing steps which operate on the entire sector.
     */
    if(sector_index == (DENGR_CDDA_SECTOR_SIZE - 1)) {
        // reverse the CIRC encoding and 'scrambling' system
        context->sector = dengr_reverse_sector_encoding(context->sector);
        // flush the data out to be written
        context->write_sector_callback(
            context->sector_count,
            context->sector,
            context->write_sector_data
        );
        // increment sector count
        context->sector_count++;
    }
}

static uint8_t dengr_get_efm_byte_for_pixel(dengr_pixel_t pixel) {
    switch(pixel) {
        case DENGR_PIXEL_BLACK:
            return 0x30; // 00000100000000 in EFM
        case DENGR_PIXEL_WHITE:
            return 0xAA; // 10010001001001 in EFM
    }
}

static dengr_pixel_t dengr_get_pixel_at_position(
    dengr_cd_full_spec_t spec,
    dengr_co_ordinate_t position,
    dengr_bitmap_t image
) {
    // shift the co-ordinates to be only positive and in range of CD size
    position.x += spec.outer_radius;
    position.y += spec.outer_radius;
    // get the de-scaling factor for both dimensions
    long double descale_factor = (long double)spec.outer_radius * 2.0l;
    // de-scale then re-scale each dimension to the image's dimensions
    size_t x_index = ((long double)position.x / descale_factor) * image.width;
    size_t y_index = ((long double)position.y / descale_factor) * image.height;
    // apply modulo to protect from (unlikely) out-of-bounds
    return image.pixels[x_index % image.width][y_index % image.height];
}

static dengr_audio_sector_t dengr_reverse_sector_encoding(
    dengr_audio_sector_t sector
) {
    // TODO: Write actual implementation, this one just returns it as-is...
    return sector;
}

void dengr_plot_image_to_audio_file(
    dengr_cd_brief_spec_t spec,
    dengr_bitmap_t image,
    FILE* output_file
) {
    return;
}

#ifdef __cplusplus
} // extern "C"
#endif
