#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "dengr.h"


int main(int argc, char* argv[]) {
    // make sure we have enough arguments (we need 5)
    if(argc < 6) {
        fprintf(stderr, "Not enough arguments given! (Need 5)\n");
        return 1;
    }
    int64_t track_pitch, inner_radius, outer_radius;
    size_t sector_count;
    // retrieve arguments
    if(sscanf(argv[1], "%20" SCNd64, &track_pitch) != 1) {
        return 1;
    }
    if(sscanf(argv[2], "%20" SCNd64, &inner_radius) != 1) {
        return 1;
    }
    if(sscanf(argv[3], "%20" SCNd64, &outer_radius) != 1) {
        return 1;
    }
    if(sscanf(argv[4], "%20zu", &sector_count) != 1) {
        return 1;
    }
    char* output_file_name = argv[5];
    // a 'chequered' image
    dengr_pixel_t image_pixels[2][2] = {
        { DENGR_PIXEL_BLACK, DENGR_PIXEL_WHITE, },
        { DENGR_PIXEL_WHITE, DENGR_PIXEL_BLACK, },
    };
    // allocate data for the image and copy pixels across
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
    // create CD format specifications
    dengr_cd_brief_spec_t cd_brief = {
        .track_pitch = track_pitch,
        .inner_radius = dengr_mm_to_nm(inner_radius),
        .outer_radius = dengr_mm_to_nm(outer_radius),
        .sector_count = sector_count, // number of sectors on my CD-RW discs
    };
    // get full specs of CD format
    dengr_cd_full_spec_t cd_specs = dengr_brief_spec_to_full_spec(cd_brief);
    printf("CD accessible data in bytes: %zu\n", cd_specs.capacity);
    printf("CD track length in nm: %" PRId64 "\n", cd_specs.track_length);
    // open file for writing output to
    FILE* file_handle = fopen(output_file_name, "wb");
    // guard against error opening file
    assert(file_handle != NULL);
    // convert image to audio data and save to file
    dengr_plot_image_to_audio_file(cd_brief, image, file_handle);
    // close file
    fclose(file_handle);
    return 0;
}
