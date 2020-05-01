#ifndef COM_SAXBOPHONE_DENGR_F3_FRAME
#define COM_SAXBOPHONE_DENGR_F3_FRAME

#include "Byte.hpp"
#include "F2Frame.hpp"


namespace com::saxbophone::dengr {
    /**
     * @brief One F₃-Frame consisting of the an F₂-Frame with a Control byte
     * prepended
     * @details Definition from @e ECMA-130, sec. 4.7:
     * @details A group of 33 8-bit bytes, being an F2-Frame with a control
     * byte, and input to a 8-to-14 encoder.
     */
    struct F3Frame : public F2Frame {
        /**
         * @brief The Control Byte for this F₃-Frame
         * @details Control Bytes are derived according to ECMA-130, sec. 22
         */
        Byte control_byte;
    };
}

#endif // include guard
