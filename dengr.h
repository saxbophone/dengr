// include guard
#ifndef SAXBOPHONE_DENGR_DENGR_H
#define SAXBOPHONE_DENGR_DENGR_H

#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C"{
#endif

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

dengr_audio_samples_t dengr_seconds_to_samples(dengr_audio_seconds_t seconds);

dengr_audio_samples_t dengr_minutes_to_samples(dengr_audio_minutes_t minutes);

dengr_cd_full_spec_t dengr_brief_spec_to_full_spec(dengr_cd_brief_spec_t brief);

#ifdef __cplusplus
} // extern "C"
#endif

// end of include guard
#endif
