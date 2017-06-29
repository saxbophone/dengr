// include guard
#ifndef SAXBOPHONE_DENGR_DENGR_H
#define SAXBOPHONE_DENGR_DENGR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C"{
#endif

// millimetres type
typedef int64_t dengr_millimetre_t;
/*
 * a nanometre (nm) is one billionth of a metre, hence we need a range that can
 * represent ~6km in nm (6,000,000,000,000) and then some. It also needs to be
 * negative for convenience when dealing in 2-dimensional space.
 */
typedef int64_t dengr_nanometre_t;
// measures audio length in samples
typedef uint32_t dengr_audio_samples_t;
// measures audio length in seconds
typedef uint16_t dengr_audio_seconds_t;
// measures audio length in minutes
typedef uint8_t dengr_audio_minutes_t;

/*
 * this struct stores basic data about a CD's specifications
 * this is the sort of data a user could find out themselves
 */
typedef struct dengr_cd_brief_spec_t {
    dengr_nanometre_t track_pitch;
    dengr_nanometre_t inner_radius;
    dengr_nanometre_t outer_radius;
    dengr_audio_samples_t play_time;
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
typedef bool dengr_pixel_t;

// bitmap image type
typedef struct dengr_bitmap_t {
    size_t width;
    size_t height;
    dengr_pixel_t** pixels;
} dengr_bitmap_t;

// CD Digital Audio sample rate
extern const dengr_audio_samples_t DENGR_CDDA_SAMPLE_RATE;
// constants for the pixel colour values
extern const dengr_pixel_t DENGR_PIXEL_BLACK;
extern const dengr_pixel_t DENGR_PIXEL_WHITE;

// convert a measurement in mm to nm (nanometres)
dengr_nanometre_t dengr_mm_to_nm(dengr_millimetre_t mm);

// convert a unit of time in seconds to samples
dengr_audio_samples_t dengr_seconds_to_samples(dengr_audio_seconds_t seconds);

// convert a unit of time in minutes to samples
dengr_audio_samples_t dengr_minutes_to_samples(dengr_audio_minutes_t minutes);

// for a user-supplied description of a CD, derive more detailed data about it
dengr_cd_full_spec_t dengr_brief_spec_to_full_spec(dengr_cd_brief_spec_t brief);

/*
 * for a given full CD spec, a maximum number of points to plot (no limit set if
 * 0), a pointer to custom data of a user-defined type and a callback to a
 * function which receives each co-ordinate, index of point found and the custom
 * data pointer as arguments, find all the x-y co-ordinates of the CD and call
 * the given callback with each x-y co-ordinate found (and the user data too)
 */
void dengr_trace_cd_spiral(
    dengr_cd_full_spec_t spec, size_t max_points,
    void(* callback)(
        dengr_co_ordinate_t co_ordinate,
        size_t index,
        void* user_data
    ),
    void* user_data
);

/*
 * for a given full CD spec, x-y co-ordinates of a point on a CD pertaining to
 * that CD spec and a bitmap image, find the image pixel which is located at the
 * given x-y co-ordinates if the image was mapped at a 1:1 ratio to the CD
 * program area
 */
dengr_pixel_t dengr_get_pixel_at_position(
    dengr_cd_full_spec_t spec,
    dengr_co_ordinate_t position,
    dengr_bitmap_t image
);

/*
 * for a given full CD spec, an image to plot, a callback into which raw audio
 * data is sent and a pointer to custom data of a user-defined type, convert the
 * image to raw 16-bit signed PCM audio, which is written out through the write
 * callback.
 */
void dengr_plot_image_to_audio(
    dengr_cd_full_spec_t spec,
    dengr_bitmap_t image,
    void(* write_callback)(uint8_t item, void* user_data),
    void* user_data
);

#ifdef __cplusplus
} // extern "C"
#endif

// end of include guard
#endif
