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
#ifndef COM_SAXBOPHONE_DENGR_MERGING_BITS
#define COM_SAXBOPHONE_DENGR_MERGING_BITS

#include <cstdint>


// TODO: Change to namespace com::saxbophone::dengr when move to C++20 complete
namespace com::saxbophone::dengr {
    /**
     * @brief A sequence of 3 Channel bits delimiting each part of a Channel
     * Frame to prevent encoding issues.
     * @details See @e ECMA-130, secs. 19.3 and 19.4 for more information.
     * @warn Don't set the 5 most significant bits of this type. It's declared
     * as 8-bit because 3-bit isn't an option, but it should be used as if it's
     * 3-bit. It might be packed into a 3-bit bitfield in structures that use
     * it.
     */
    typedef std::uint8_t MergingBits;
}

#endif // include guard
