#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "dengr.h"


// user data for callback
struct my_user_data {
    dengr_cd_full_spec_t* spec;
    dengr_bitmap_t* image;
};

static void my_callback(dengr_co_ordinate_t co_ordinate, void* user_data) {
    // retrieve user data
    struct my_user_data data = *(struct my_user_data*)user_data;
    printf(
        "%d",
        dengr_get_pixel_at_position(
            *data.spec,
            co_ordinate,
            *data.image
        )
    );
}

int main(void) {
    // a 'chequered' image
    dengr_pixel_t image_pixels[2][2] = {
        { DENGR_PIXEL_BLACK, DENGR_PIXEL_WHITE, },
        { DENGR_PIXEL_WHITE, DENGR_PIXEL_BLACK, },
    };
    dengr_bitmap_t image = {
        .width = 2,
        .height = 2,
        .pixels = calloc(2, sizeof(dengr_pixel_t*)),
    };
    for(size_t x = 0; x < 2; x++) {
        image.pixels[x] = calloc(2, sizeof(dengr_pixel_t));
        for(size_t y = 0; y < 2; y++) {
            image.pixels[x][y] = image_pixels[x][y];
        }
    }
    // a CD format with loads of assumptions about it being a 'standard CD-R'
    dengr_cd_brief_spec_t cd_brief = {
        .track_pitch = 1500,
        .inner_radius = dengr_mm_to_nm(25),
        .outer_radius = dengr_mm_to_nm(58),
        .play_time = dengr_minutes_to_samples(80),
    };
    // get full specs of CD format
    dengr_cd_full_spec_t cd_specs = dengr_brief_spec_to_full_spec(cd_brief);
    printf("CD audio data in bytes: %zu\n", cd_specs.capacity);
    printf("CD track length in nm: %" PRId64 "\n", cd_specs.track_length);
    // set up user data
    struct my_user_data user_data = {
        .spec = &cd_specs,
        .image = &image,
    };
    // trace the spiral!
    dengr_trace_cd_spiral(cd_specs, 0, my_callback, (void*)&user_data);
    return 0;
}
