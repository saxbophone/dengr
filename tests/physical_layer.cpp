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

#include <catch2/catch.hpp>

#include "ChannelBit.hpp"
#include "Pit.hpp"
#include "physical_layer.hpp"


using namespace com::saxbophone::dengr;
using namespace com::saxbophone::dengr::physical_layer;

SCENARIO("Sequences of bits can be converted to/from sequences of pits/lands") {
    const std::size_t LENGTH = 8;
    // convenience typedef to keep the test case data lines within limits
    typedef std::tuple<Pit, std::uint8_t, std::uint8_t> TestData;
    /*
     * MSVC Warning C4244 produces spurious warnings for implicit type
     * conversions in the call to GENERATE(). We disable this warning for
     * this statement as the alternative (to silence the warning) involves
     * en-masse repetition of types in a truly redundant manner (readability).
     */
    #if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4244 )
    #endif
    // bits are stuffed into uints here for compactness
    auto bits_pits_combination = GENERATE(
        //    previous-pit  bits        pits
        TestData(Pit::LAND, 0b01101001, 0b01001110),
        TestData(Pit::PIT , 0b01101001, 0b10110001),
        TestData(Pit::LAND, 0b11101010, 0b10110011),
        TestData(Pit::PIT , 0b00110011, 0b11011101),
        TestData(Pit::PIT , 0b00100100, 0b11000111),
        TestData(Pit::LAND, 0b00010000, 0b00011111),
        TestData(Pit::LAND, 0b11001101, 0b10001001),
        TestData(Pit::PIT , 0b11110111, 0b01011010),
        TestData(Pit::LAND, 0b10010010, 0b11100011),
        TestData(Pit::PIT , 0b00010010, 0b11100011),
        TestData(Pit::PIT , 0b10000000, 0b00000000),
        TestData(Pit::LAND, 0b00000000, 0b00000000)
    );
    #if defined(_MSC_VER)
    #pragma warning( pop )
    #endif
    // extract the bit patterns for use in the test case
    ChannelBitArray<LENGTH> bits = {};
    PitArray<LENGTH> pits = {};
    // also extract the previous pit value
    Pit previous_pit = std::get<0>(bits_pits_combination);
    for (std::uint8_t i = 0; i < 8; i++) {
        bits[i] = (std::get<1>(bits_pits_combination) & (1 << (7 - i))) != 0;
        pits[i] = (Pit)((std::get<2>(bits_pits_combination) & (1 << (7 - i))) != 0);
    }

    GIVEN("A sequence of Channel Bits and its corresponding sequence of pits/lands") {
        WHEN("The bits are passed into the pit/land encoder") {
            PitArray<LENGTH> output = bits_to_pits(previous_pit, bits);
            THEN("The encoder should return a corresponding sequence of pits/lands") {
                // output should be equal to pits, which is what's expected
                REQUIRE(output == pits);
            }
        }
    }

    GIVEN("A sequence of pits/lands and its corresponding sequence of Channel Bits") {
        WHEN("The pits/lands are passed into the pit/land decoder") {
            ChannelBitArray<LENGTH> output = pits_to_bits(previous_pit, pits);
            THEN("The decoder should return a corresponding sequence of bits") {
                // output should be equal to bits, which is what's expected
                REQUIRE(output == bits);
            }
        }
    }
}
