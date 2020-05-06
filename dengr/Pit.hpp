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
#ifndef COM_SAXBOPHONE_DENGR_PIT
#define COM_SAXBOPHONE_DENGR_PIT

// TODO: Change to namespace com::saxbophone::dengr when move to C++20 complete
namespace com::saxbophone::dengr {
    /**
     * @brief A single Pit or Land on the physical reflective layer of the disc
     * @remarks This represents the NRZI-encoded version of the sequence of
     * Channel Bits formed by the data in a Channel Frame.
     * @details Definition of the pits/lands can be found in ECMA-130, sec. 11.1
     * @details Definition of how Channel Bits are encoded into these can be
     * found in ECMA-130, sec. 19.4
     */
    enum Pit : bool {
        PIT = true,   /**< A depression on the track's surface */
        LAND = false, /**< A flat area on the track's surface */
    };
}

#endif // include guard
