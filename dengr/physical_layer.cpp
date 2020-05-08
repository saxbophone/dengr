/*
 * This source file forms part of DENGR, a piece of software which
 * produces disc images which produce visible images on the recording side when
 * burned to Compact Disc.
 *
 * Copyright (C) 2020 Joshua Saxby <joshua.a.saxby@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <array>

#include <cstddef>

#include "ChannelBit.hpp"
#include "Pit.hpp"


namespace com::saxbophone::dengr::physical_layer {
    template<std::size_t LENGTH>
    std::array<Pit, LENGTH> bits_to_pits(
        Pit previous_pit,
        std::array<ChannelBit, LENGTH> bits
    ) {
        // XXX: stub implementation returning all zeroes
        // XXX: WRITE UNIT TESTS BEFORE IMPLEMENTATION, JOSH!
        std::array<Pit, LENGTH> pits;
        return pits;
    }

    template<std::size_t LENGTH>
    std::array<ChannelBit, LENGTH> pits_to_bits(
        Pit previous_pit,
        std::array<Pit, LENGTH> pits
    ) {
        // XXX: stub implementation returning all zeroes
        // XXX: WRITE UNIT TESTS BEFORE IMPLEMENTATION, JOSH!
        std::array<ChannelBit, LENGTH> bits;
        return bits;
    }
}
