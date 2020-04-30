#ifndef COM_SAXBOPHONE_DENGR_MODE_2_SECTOR
#define COM_SAXBOPHONE_DENGR_MODE_2_SECTOR

#include <array>

#include "Byte.hpp"


// TODO: Change to namespace com::saxbophone::dengr when move to C++20 complete
namespace dengr {
    /**
     * @brief One chunk of user data to be encoded and written to disc
     * @note This is a RAW CD-ROM Mode 2 Sector consisting of 2352 Bytes
     * (see ECMA-130 sec. 14). As it is in RAW format, it includes not only the
     * User Data section, but the Sync and Header sections as well, which we can
     * set to whatever we like as this library is designed for writing images to
     * disc in RAW mode.
     * @details Definition from @e ECMA-130, sec. 4.14:
     * @details The smallest addressable part of a Digital Data Track in the
     * information area that can be accessed independently of other addressable
     * parts of the area.
     * @remarks This is the highest-level data structure for storing user data
     * modelled by this library.
     */
    struct Mode2Sector {
        /**
         * @brief The Bytes that make up the data contained in this Sector
         * @warn At this point, we are deviating from the ECMA-130 standard as
         * we are appropriating the first 16 bytes that are supposed to be
         * reserved for Sync pattern and addressing Header, for usage as our own
         * data. User Data isn't actually supposed to take up more than 2336
         * Bytes in CD-ROM Mode 2, but this software is designed to produce BIN
         * images that are to be written in RAW mode to disc. Omitting the sync
         * and address header probably makes the discs unreadable in normal
         * usage, but we don't care about that after all.
         */
        std::array<Byte, 2352> bytes;
    };
}

#endif // include guard
