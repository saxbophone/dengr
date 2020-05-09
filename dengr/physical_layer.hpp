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
#ifndef COM_SAXBOPHONE_DENGR_PHYSICAL_LAYER
#define COM_SAXBOPHONE_DENGR_PHYSICAL_LAYER

#include <array>

#include <cstddef>

#include "ChannelBit.hpp"
#include "Pit.hpp"


/**
 * @brief Functions for encoding sequences of bits to sequences of Pits/Lands
 * @details This implements the process described towards the end of ECMA-130,
 * sec 19.4
 */
namespace com::saxbophone::dengr::physical_layer {
    /**
     * @brief Encodes an array of Channel Bits into an equal-sized array of Pits
     * @details This uses Non-Return-to-Zero-Inverted (NRZI) encoding to encode
     * bits into pits.
     * @tparam LENGTH the length of the input and output arrays
     * @param previous_pit the value of the previous Pit seen immediately before
     * this upcoming array of Pits to be encoded
     * @param bits the array of Channel Bits to encode
     * @returns array of Pits representing the given input bits
     */
    template<std::size_t LENGTH>
    PitArray<LENGTH> bits_to_pits(
        Pit previous_pit,
        ChannelBitArray<LENGTH> bits
    );

    /**
     * @brief Decodes an array of Pits into an equal-sized array of Channel Bits
     * @details This uses Non-Return-to-Zero-Inverted (NRZI) encoding to decode
     * pits into bits
     * @tparam LENGTH the length of the input and output arrays
     * @param previous_pit the value of the previous Pit seen immediately before
     * this upcoming array of Pits to be decoded
     * @param pits the array of Pits to decode
     * @returns array of Channel Bits represented by the given input Pits
     */
    template<std::size_t LENGTH>
    ChannelBitArray<LENGTH> pits_to_bits(
        Pit previous_pit,
        PitArray<LENGTH> pits
    );
}

// because these functions are templated, their implementation follows immediately
#include "physical_layer.inl"

#endif // include guard
