#include <math.h>
#include <stddef.h>

#include "dengr.h"


#ifdef __cplusplus
extern "C"{
#endif

const dengr_audio_samples_t DENGR_CDDA_SAMPLE_RATE = 44100;

dengr_audio_samples_t dengr_seconds_to_samples(dengr_audio_seconds_t seconds) {
    return (dengr_audio_samples_t)seconds * DENGR_CDDA_SAMPLE_RATE;
}

dengr_audio_samples_t dengr_minutes_to_samples(dengr_audio_minutes_t minutes) {
    return dengr_seconds_to_samples((dengr_audio_seconds_t)minutes * 60);
}

static dengr_nanometre_t dengr_get_cd_track_length(
    dengr_cd_brief_spec_t brief
);

static size_t dengr_get_size_of_play_time_in_bytes(
    dengr_audio_samples_t play_time
);

dengr_cd_full_spec_t dengr_brief_spec_to_full_spec(
    dengr_cd_brief_spec_t brief
) {
    return (dengr_cd_full_spec_t) {
        .track_pitch = brief.track_pitch,
        .track_length = dengr_get_cd_track_length(brief),
        .inner_radius = brief.inner_radius,
        .outer_radius = brief.outer_radius,
        .capacity = dengr_get_size_of_play_time_in_bytes(brief.play_time),
    };
}

dengr_co_ordinate_t dengr_get_position_of_audio_byte(
    dengr_cd_full_spec_t spec,
    size_t audio_byte_index
) {
    // NOTE: This code is not correct! Change it to actually work it out.
    return (dengr_co_ordinate_t) { .x = 0, .y = 0, };
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

static size_t dengr_get_size_of_play_time_in_bytes(
    dengr_audio_samples_t play_time
) {
    // each sample is doubled because it's in stereo. each sample is 2 bytes
    return (size_t)play_time * 2 * 2;
}

#ifdef __cplusplus
} // extern "C"
#endif
