#ifndef COM_SAXBOPHONE_DENGR_SECTION
#define COM_SAXBOPHONE_DENGR_SECTION

#include <array>

#include "F3Frame.hpp"


namespace com::saxbophone::dengr {
    /**
     * @brief A group of 98 consecutive F₃-Frames
     * @details Definition from @e ECMA-130, sec. 4.13:
     * @details A group of 98 F3-Frames containing one complete table of Control
     * bytes.
     */
    struct Section {
        /**
         * @brief The F₃-Frames that comprise this Section
         */
        std::array<F3Frame, 98> frames;
    };
}

#endif // include guard
