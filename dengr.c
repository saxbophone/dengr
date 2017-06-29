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

const size_t DENGR_CDROM_MODE_2_SECTOR_DATA_SIZE = 2336;

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
    return brief.sector_count * DENGR_CDROM_MODE_2_SECTOR_DATA_SIZE;
}

static dengr_co_ordinate_t dengr_polar_to_cartesian(
    long double radius, long double angle
) {
    return (dengr_co_ordinate_t){
        .x = (dengr_nanometre_t)(radius * cosl(angle * 2.0l * M_PI)),
        .y = (dengr_nanometre_t)(radius * sinl(angle * 2.0l * M_PI)),
    };
}

#ifdef __cplusplus
} // extern "C"
#endif
