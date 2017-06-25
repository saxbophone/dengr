#include "dengr.h"


int main(void) {
    // a 'chequered' image
    dengr_pixel_t image_pixels[2][2] = {
        { DENGR_PIXEL_BLACK, DENGR_PIXEL_WHITE, },
        { DENGR_PIXEL_WHITE, DENGR_PIXEL_BLACK, },
    };
    dengr_bitmap_t image = {
        .width = 2,
        .height = 2,
        .pixels = image_pixels, // FIXME: This isn't correct...
    };
    // a CD format with loads of assumptions about it being a 'standard CD-R'
    dengr_cd_brief_spec_t cd_brief = {
        .track_pitch = 160,
        .inner_radius = dengr_mm_to_nm(25),
        .outer_radius = dengr_mm_to_nm(58),
        .play_time = dengr_minutes_to_samples(80),
    };
    // get full specs of CD format
    dengr_cd_full_spec_t cd_specs = dengr_brief_spec_to_full_spec(cd_brief);
    return 0;
}
