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
#ifndef COM_SAXBOPHONE_DENGR_CHANNEL_BIT
#define COM_SAXBOPHONE_DENGR_CHANNEL_BIT

#include <array>


namespace com::saxbophone::dengr {
    /**
     * @brief Each Channel Frame comprises 588 Channel bits, these are those bits
     */
    typedef bool ChannelBit;

    /**
     * @brief Convenience typedef to allow making arrays of channel bits easier
     * @tparam LENGTH the length of the ChannelBitArray
     */
    template<std::size_t LENGTH>
    using ChannelBitArray = std::array<ChannelBit, LENGTH>;
}

#endif // include guard
