#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "dengr.h"


// user data for callback
struct my_user_data {
    dengr_cd_full_spec_t* spec;
    dengr_bitmap_t* image;
};

static void my_callback(dengr_co_ordinate_t co_ordinate, size_t i, void* user_data) {
    static size_t sames;
    static dengr_pixel_t current_colour;
    // retrieve user data
    struct my_user_data data = *(struct my_user_data*)user_data;
    dengr_pixel_t next_colour = dengr_get_pixel_at_position(
        *data.spec,
        co_ordinate,
        *data.image
    );
    if(current_colour == next_colour) {
        sames++;
    } else {
        current_colour = next_colour;
        printf("%zu %zu\n", i, sames);
        sames = 0;
    }
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
        // for some reason, my discs store 79:57 (mm:ss) of audio
        .play_time = dengr_minutes_to_samples(80) - dengr_seconds_to_samples(3),
    };
    // get full specs of CD format
    dengr_cd_full_spec_t cd_specs = dengr_brief_spec_to_full_spec(cd_brief);
    printf("CD audio data in bytes: %zu\n", cd_specs.capacity);
    printf("CD track length in nm: %" PRId64 "\n", cd_specs.track_length);
    // convert image to audio
    dengr_plot_image_to_audio(cd_specs, image, NULL, NULL);
    return 0;
}
