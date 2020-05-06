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
#ifndef COM_SAXBOPHONE_DENGR_CHANNEL_BYTE
#define COM_SAXBOPHONE_DENGR_CHANNEL_BYTE

#include <cstdint>


namespace com::saxbophone::dengr {
    /**
     * @brief A 14-bit "byte", as output from the 8-to-14 modulator
     * @details This is the last layer of data encoding before the physical
     * layer of Pits and Lands is reached on the recording surface of the disc
     * itself.
     * @note "Channel Byte" is not an official term used within the reference
     * standard (ECMA-130) itself, but is used in this library as a term of
     * convenience for the alternative which would be "14-bit byte" (this is
     * incidentally, similar to the phrasing used in ECMA-130).
     * @warn Don't set the two most significant bits of this type. It's declared
     * as 16-bit because 14-bit isn't an option, but it should be used as if
     * it's 14-bit. It might be packed into a 14-bit bitfield in structures that
     * use it.
     */
    typedef std::uint16_t ChannelByte;
}

#endif // include guard
