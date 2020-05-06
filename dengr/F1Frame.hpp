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
#ifndef COM_SAXBOPHONE_DENGR_F1_FRAME
#define COM_SAXBOPHONE_DENGR_F1_FRAME

#include <array>

#include "Byte.hpp"


namespace com::saxbophone::dengr {
    /**
     * @brief One F₁-Frame consisting of the re-arranged bytes of one part of a
     * Scrambled Sector
     * @details Definition from @e ECMA-130, sec. 4.5:
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
