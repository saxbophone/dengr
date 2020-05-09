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
#include <tuple>

#include <cstddef>

#include "../vendor/catch.hpp"

#include "../dengr/ChannelBit.hpp"
#include "../dengr/Pit.hpp"
#include "../dengr/physical_layer.hpp"


using namespace com::saxbophone::dengr;
using namespace com::saxbophone::dengr::physical_layer;

SCENARIO("Sequences of bits can be converted to sequences of pits/lands") {
    GIVEN("A sequence of Channel Bits and its corresponding sequence of pits/lands") {
        const std::size_t LENGTH = 8;
        // bits are stuffed into uints here for compactness
        auto bits_pits_combination = GENERATE(
            // previous-pit pits          expected-bits
            std::tuple<Pit, std::uint8_t, std::uint8_t>(Pit::LAND, 0b01101001, 0b01001110)
        );
        // extract the bit patterns for use in the test case
        ChannelBitArray<LENGTH> bits;
        PitArray<LENGTH> pits;
        for (std::uint8_t i = 0; i < 8; i++) {
            bits[i] = (std::get<1>(bits_pits_combination) & (1 << (7 - i))) != 0;
            pits[i] = (Pit)((std::get<2>(bits_pits_combination) & (1 << (7 - i))) != 0);
        }
        WHEN("The bits are passed into the pit/land encoder") {
            // also extract the previous pit value
            PitArray<LENGTH> output = bits_to_pits(std::get<0>(bits_pits_combination), bits);
            THEN("The encoder should return a corresponding sequence of pits/lands") {
                // output should be equal to pits, which is what's expected
                REQUIRE(output == pits);
            }
        }
    }
}
