#include <math.h>
#include <stdint.h>


/*
 * a nanometre (nm) is one billionth of a metre, hence we need a range that can
 * represent ~6km in nm (6,000,000,000,000) and then some. It also needs to be
 * negative for convenience when dealing in 2-dimensional space.
 */
typedef int64_t nanometre_t;

// this struct stores data describing the measurements of a given CD format
typedef struct cd_format_t {
    nanometre_t track_pitch;
    nanometre_t inner_radius;
    nanometre_t outer_radius;
    nanometre_t track_length;
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

static cd_format_t make_cd_format(
    nanometre_t track_pitch,
    nanometre_t inner_radius,
    nanometre_t outer_radius
) {
    cd_format_t format = {
        .track_pitch = track_pitch,
        .inner_radius = inner_radius,
        .outer_radius = outer_radius,
    };
    format.track_length = get_cd_track_length(format);
    return format;
}
