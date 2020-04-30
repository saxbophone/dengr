#ifndef COM_SAXBOPHONE_DENGR_F1_FRAME
#define COM_SAXBOPHONE_DENGR_F1_FRAME

#include <array>

#include "Byte.hpp"


// TODO: Change to namespace com::saxbophone::dengr when move to C++20 complete
namespace dengr {
    /**
     * @brief One F₁-Frame consisting of the re-arranged bytes of one part of a
     * Scrambled Sector
     * @details Definition from @eECMA-130, sec. 4.5:
     * @details A group of 24 8-bit bytes, being the output of a scrambler and
     * input to a CIRC encoder.
     */
    struct F1Frame {
        /**
         * @brief The Bytes contained within this F₁-Frame
         */
        std::array<Byte, 24> bytes;
    };
}

#endif // include guard
