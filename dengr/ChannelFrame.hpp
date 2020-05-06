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
#ifndef COM_SAXBOPHONE_DENGR_CHANNEL_FRAME
#define COM_SAXBOPHONE_DENGR_CHANNEL_FRAME

#include <array>

#include <cstdint>

#include "ChannelByte.hpp"
#include "MergingBits.hpp"


namespace com::saxbophone::dengr {
    /**
     * @brief One Channel Frame consisting of an F₃-Frame converted to 14-bit
     * Bytes (Channel Bytes) and with additional fields added.
     * @details See @e ECMA-130, sec 19.4 for more information.
     * @note Bitfields are used extensively in this type. These serve primarily
     * as a documentation aid rather than to promote efficient data packing. At
     * this level, the bit-length of the fields are very specific in ECMA-130.
     */
    struct ChannelFrame {
        /**
         * @note This is always a fixed value.
         * @details As per ECMA-130, sec 19.2, this shall always be following:
         * `100000000001000000000010`
         * @warn This is a 24-bit value.
         */
        static const std::uint32_t SYNC_HEADER;
        /**
         * @brief Merging Bits to separate the Sync Header and the Control Byte
         */
        MergingBits sync_header_delimiter : 3;
        /**
         * @brief This should be the Control Byte as generated in the F₃-Frame
         * verbatim.
         */
        ChannelByte control_byte : 14;
        /**
         * @brief Merging Bits to separate the Control Byte from the rest of the
         * data in the Channel Frame.
         */
        MergingBits control_byte_delimiter : 3;

        /**
         * @brief Used internally by ChannelFrame to pack Channel Bytes with
         * their Merging Bits so they can be used in an array conveniently.
         */
        struct ChannelByteWithMergingBits {
            ChannelByte byte : 14;
            MergingBits merging_bits : 3;
        };

        /**
         * @brief Each Channel Byte (this is now the frame data) must be
         * followed by 3 Merging Bits. There are 32 such combinations altogether
         */
        std::array<ChannelByteWithMergingBits, 32> packed_channel_bytes;
    };
}

#endif // include guard
