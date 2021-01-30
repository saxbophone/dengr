/**
 * @file
 *
 * @remarks This source file forms part of DENGR, a piece of software which
 * produces disc images which produce visible images on the recording side when
 * burned to Compact Disc.
 *
 * @author Joshua Saxby <joshua.a.saxby@gmail.com>
 * @date 2020
 *
 * @copyright Copyright (C) 2020 Joshua Saxby
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * @copyright
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * @copyright
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef COM_SAXBOPHONE_DENGR_MODE_2_SECTOR
#define COM_SAXBOPHONE_DENGR_MODE_2_SECTOR

#include <array>

#include "Byte.hpp"


namespace com::saxbophone::dengr {
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
         * @warning At this point, we are deviating from the ECMA-130 standard as
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
