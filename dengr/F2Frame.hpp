#ifndef COM_SAXBOPHONE_DENGR_F2_FRAME
#define COM_SAXBOPHONE_DENGR_F2_FRAME

#include <array>

#include "Byte.hpp"


namespace com::saxbophone::dengr {
    /**
     * @brief One F₂-Frame consisting of the CIRC-encoded bytes of an F₁-Frame
     * @details Definition from @e ECMA-130, sec. 4.6:
     * @details A group of 32 8-bit bytes, being the output of a CIRC encoder.
     */
    struct F2Frame {
        /**
         * @brief The Bytes contained within this F₂-Frame
         */
        std::array<Byte, 32> bytes;
    };
}

#endif // include guard
