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
#include <utility>

#include <cstddef>

#include "ChannelBit.hpp"
#include "Pit.hpp"


namespace com::saxbophone::dengr::physical_layer {
    template<std::size_t LENGTH>
    PitArray<LENGTH> bits_to_pits(
        Pit previous_pit,
        ChannelBitArray<LENGTH> bits
    ) {
        // used to keep track of what the current Pit/Land status is
        std::pair<Pit, Pit> state = { Pit::LAND, Pit::PIT, };
        // the first item is used as "current state", so swap if previous is PIT
        if (previous_pit == Pit::PIT) {
            std::swap(state.first, state.second);
        }
        PitArray<LENGTH> pits;
        for (std::size_t i = 0; i < LENGTH; i++) {
            // for each bit seen, if it's 1, swap states, otherwise, leave as-is
            if (bits[i] == 0b1) {
                std::swap(state.first, state.second);
            }
            // output the state in the first position of the pair
            pits[i] = state.first;
        }
        return pits;
    }

    template<std::size_t LENGTH>
    ChannelBitArray<LENGTH> pits_to_bits(
        Pit previous_pit,
        PitArray<LENGTH> pits
    ) {
        ChannelBitArray<LENGTH> bits = {};
        for (std::size_t i = 0; i < LENGTH; i++) {
            // as long as the pit is the same as previous, send 0
            if (pits[i] == previous_pit) {
                bits[i] = 0b0;
            } else {
                // otherwise, send 1 and update the "previous pit" to last-seen
                bits[i] = 0b1;
                previous_pit = pits[i];
            }
        }
        return bits;
    }
}
