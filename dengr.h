// include guard
#ifndef SAXBOPHONE_DENGR_DENGR_H
#define SAXBOPHONE_DENGR_DENGR_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C"{
#endif

// the number of audio bytes per-sector of red-book audio CDs
#define DENGR_CDDA_SECTOR_SIZE 2352

// millimetres type
typedef int64_t dengr_millimetre_t;
/*
 * a nanometre (nm) is one billionth of a metre, hence we need a range that can
 * represent ~6km in nm (6,000,000,000,000) and then some. It also needs to be
 * negative for convenience when dealing in 2-dimensional space.
 */
typedef int64_t dengr_nanometre_t;

/*
 * this struct stores basic data about a CD's specifications
 * this is the sort of data a user could find out themselves
 */
typedef struct dengr_cd_brief_spec_t {
    dengr_nanometre_t track_pitch;
    dengr_nanometre_t inner_radius;
    dengr_nanometre_t outer_radius;
    size_t sector_count;
} dengr_cd_brief_spec_t;

/*
 * this struct stores full data about a CD's specifications
 * this is the set of data needed by the algorithm to plot the spiral of the CD
 * and contains data which is derived from the brief spec, but which would be
 * unwieldy for the user to handle
 */
typedef struct dengr_cd_full_spec_t {
    dengr_nanometre_t track_pitch;
    dengr_nanometre_t track_length;
    dengr_nanometre_t inner_radius;
    dengr_nanometre_t outer_radius;
    size_t capacity;
} dengr_cd_full_spec_t;

// an x-y point in cartesian space
typedef struct dengr_co_ordinate_t {
    dengr_nanometre_t x;
    dengr_nanometre_t y;
} dengr_co_ordinate_t;

// image pixel type
typedef enum dengr_pixel_t {
    DENGR_PIXEL_BLACK,
    DENGR_PIXEL_WHITE,
} dengr_pixel_t;

// bitmap image type
typedef struct dengr_bitmap_t {
    size_t width;
    size_t height;
    dengr_pixel_t** pixels;
} dengr_bitmap_t;

// one CD audio sector's worth of audio bytes
typedef struct dengr_audio_sector_t {
    uint8_t data[DENGR_CDDA_SECTOR_SIZE];
} dengr_audio_sector_t;

// convert a measurement in mm to nm (nanometres)
dengr_nanometre_t dengr_mm_to_nm(dengr_millimetre_t mm);

// for a user-supplied description of a CD, derive more detailed data about it
dengr_cd_full_spec_t dengr_brief_spec_to_full_spec(dengr_cd_brief_spec_t brief);

/*
 * Produces a stream of raw LPCM CD Audio which when written to a CD as a red
 * book audio disc will make an image appear on the recoding side of the disc.
 */
void dengr_plot_image_to_audio(
    dengr_cd_full_spec_t spec,
    dengr_bitmap_t image,
    void(* write_sector)(
        size_t sector_index,
        dengr_audio_sector_t sector,
        void* write_sector_data
    ),
    void* write_sector_data
);

/*
 * Does the same thing as dengr_plot_image_to_audio(), except the raw LPCM CD
 * Audio is written to the given file handle instead.
 */
void dengr_plot_image_to_audio_file(
    dengr_cd_brief_spec_t spec,
    dengr_bitmap_t image,
    FILE* output_file
);

#ifdef __cplusplus
} // extern "C"
#endif

// end of include guard
#endif
