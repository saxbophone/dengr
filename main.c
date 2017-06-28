#include <inttypes.h>
#include <stdio.h>

#include "dengr.h"


static void my_callback(dengr_co_ordinate_t co_ordinate, void* user_data) {
    static dengr_nanometre_t max_x = 0;
    static dengr_nanometre_t max_y = 0;
    if(co_ordinate.x > max_x || co_ordinate.y > max_y) {
        printf("(%" PRId64 ", %" PRId64 ")\n", co_ordinate.x, co_ordinate.y);
    }
    if(co_ordinate.x > max_x) {
        max_x = co_ordinate.x;
    }
    if(co_ordinate.y > max_y) {
        max_y = co_ordinate.y;
    }
}

int main(void) {
    // a 'chequered' image
    // dengr_pixel_t image_pixels[2][2] = {
    //     { DENGR_PIXEL_BLACK, DENGR_PIXEL_WHITE, },
    //     { DENGR_PIXEL_WHITE, DENGR_PIXEL_BLACK, },
    // };
    // dengr_bitmap_t image = {
    //     .width = 2,
    //     .height = 2,
    //     .pixels = image_pixels, // FIXME: This isn't correct...
    // };
    // a CD format with loads of assumptions about it being a 'standard CD-R'
    dengr_cd_brief_spec_t cd_brief = {
        .track_pitch = 1500,
        .inner_radius = dengr_mm_to_nm(25),
        .outer_radius = dengr_mm_to_nm(58),
        .play_time = dengr_minutes_to_samples(80),
    };
    // get full specs of CD format
    dengr_cd_full_spec_t cd_specs = dengr_brief_spec_to_full_spec(cd_brief);
    printf("CD audio data in bytes: %" PRId64 "\n", cd_specs.capacity);
    printf("CD track length in nm: %" PRId64 "\n", cd_specs.track_length);
    // trace the spiral!
    dengr_trace_cd_spiral(cd_specs, 0, my_callback, NULL);
    return 0;
}
