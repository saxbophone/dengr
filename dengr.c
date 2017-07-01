#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "dengr.h"


#ifdef __cplusplus
extern "C"{
#endif

const dengr_pixel_t DENGR_PIXEL_BLACK = false;
const dengr_pixel_t DENGR_PIXEL_WHITE = true;

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

static dengr_co_ordinate_t dengr_polar_to_cartesian(
    long double radius, long double angle
);

void dengr_trace_cd_spiral(
    dengr_cd_full_spec_t spec, size_t max_points,
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

dengr_pixel_t dengr_get_pixel_at_position(
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

static dengr_co_ordinate_t dengr_polar_to_cartesian(
    long double radius, long double angle
) {
    return (dengr_co_ordinate_t){
        .x = (dengr_nanometre_t)(radius * cosl(angle * 2.0l * M_PI)),
        .y = (dengr_nanometre_t)(radius * sinl(angle * 2.0l * M_PI)),
    };
}

struct dengr_plot_image_to_audio_data {
    void(* write_callback)(uint8_t item, void* user_data);
    void* write_callback_data;
    dengr_cd_full_spec_t* spec;
    dengr_bitmap_t* image;
    uint8_t* random_sample_buffer;
    const size_t random_sample_buffer_size;
};

struct dengr_write_raw_audio_callback_data {
    FILE* file_handle;
};

static void dengr_plot_image_to_audio_callback(
    dengr_co_ordinate_t co_ordinate,
    size_t index,
    void* user_data
);

static void dengr_write_raw_audio_callback(uint8_t item, void* user_data);

void dengr_plot_image_to_audio(
    dengr_cd_full_spec_t spec,
    dengr_bitmap_t image,
    void(* write_callback)(uint8_t item, void* user_data),
    void* user_data
) {
    // size of random sample buffer is (sample rate * 2 channels * 2 seconds)
    const size_t random_sample_buffer_size = DENGR_CDDA_SAMPLE_RATE * 2 * 2;
    // build random sample buffer
    uint8_t* random_sample_buffer = malloc(random_sample_buffer_size);
    // check we got memory back
    assert(random_sample_buffer != NULL);
    // seed the basic RNG
    const uint16_t random_seed = 0x8793;
    srand(random_seed);
    // write 'random' data to buffer
    for(size_t i = 0; i < random_sample_buffer_size; i++) {
        random_sample_buffer[i] = (uint8_t)(((double)rand() / RAND_MAX) * 256);
    }
    // set up write callback data
    struct dengr_write_raw_audio_callback_data write_callback_data = {
        .file_handle = fopen("output.pcm", "wb"),
    };
    // set up user data
    struct dengr_plot_image_to_audio_data trace_cd_spiral_callback_data = {
        .write_callback = dengr_write_raw_audio_callback,
        .write_callback_data = (void*)&write_callback_data,
        .spec = &spec,
        .image = &image,
        .random_sample_buffer = random_sample_buffer,
        .random_sample_buffer_size = random_sample_buffer_size,
    };
    // now trace the spiral to convert it to audio
    dengr_trace_cd_spiral(
        spec,
        0,
        dengr_plot_image_to_audio_callback,
        (void*)&trace_cd_spiral_callback_data
    );
    // close file
    fclose(write_callback_data.file_handle);
    // free buffer
    free(random_sample_buffer);
}

static void dengr_plot_image_to_audio_callback(
    dengr_co_ordinate_t co_ordinate,
    size_t index,
    void* user_data
) {
    // retrieve user data first
    struct dengr_plot_image_to_audio_data data = *(
        struct dengr_plot_image_to_audio_data*
    )user_data;
    // get pixel colour
    dengr_pixel_t pixel_colour = dengr_get_pixel_at_position(
        *data.spec,
        co_ordinate,
        *data.image
    );
    // if it's white get a random byte, otherwise use 0
    uint8_t output = 0x00;
    if(pixel_colour == DENGR_PIXEL_WHITE) {
        // extract the correct byte from random buffer
        output = data.random_sample_buffer[index % data.random_sample_buffer_size];
    }
    // send to write callback
    data.write_callback(output, data.write_callback_data);
}

static void dengr_write_raw_audio_callback(uint8_t item, void* user_data) {
    // retrieve user data first
    struct dengr_write_raw_audio_callback_data data = *(
        struct dengr_write_raw_audio_callback_data*
    )user_data;
    // write one byte out to file
    fwrite(&item, 1, 1, data.file_handle);
}

#ifdef __cplusplus
} // extern "C"
#endif
