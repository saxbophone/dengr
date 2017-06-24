#include <math.h>
#include <stddef.h>
#include <stdint.h>


/*
 * a nanometre (nm) is one billionth of a metre, hence we need a range that can
 * represent ~6km in nm (6,000,000,000,000) and then some. It also needs to be
 * negative for convenience when dealing in 2-dimensional space.
 */
typedef int64_t nanometre_t;
// meausring audio in seconds
typedef uint16_t audio_seconds_t;

// this struct stores data describing the measurements of a given CD format
typedef struct cd_format_t {
    nanometre_t track_pitch;
    nanometre_t track_length;
    nanometre_t inner_radius;
    nanometre_t outer_radius;
    audio_seconds_t play_time;
    size_t capacity;
} cd_format_t;

static nanometre_t get_cd_track_length(cd_format_t format) {
    return (nanometre_t)(
        (
            M_PI * (
                powl(format.outer_radius, 2.0l) -
                powl(format.inner_radius, 2.0l)
            )
        ) / format.track_pitch
    );
}

static size_t get_size_of_play_time_in_bytes(audio_seconds_t play_time) {
    // seconds of audio, sample rate, 2 channels, 2 bytes each
    return (size_t)play_time * 44100 * 2 * 2;
}

static cd_format_t make_cd_format(
    nanometre_t track_pitch,
    nanometre_t inner_radius,
    nanometre_t outer_radius,
    audio_seconds_t play_time
) {
    cd_format_t format = {
        .track_pitch = track_pitch,
        .inner_radius = inner_radius,
        .outer_radius = outer_radius,
        .play_time = play_time,
        .capacity = get_size_of_play_time_in_bytes(play_time),
    };
    format.track_length = get_cd_track_length(format);
    return format;
}
