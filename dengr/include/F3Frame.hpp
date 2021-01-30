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
