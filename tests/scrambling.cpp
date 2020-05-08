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
#include <fstream>
#include <iomanip>
#include <sstream>

#include <cstddef>

#include "../vendor/catch.hpp"

#include "../dengr/Mode2Sector.hpp"
#include "../dengr/ScrambledSector.hpp"
#include "../dengr/scrambling.hpp"


using namespace com::saxbophone::dengr;
using namespace com::saxbophone::dengr::scrambling;

SCENARIO("Sectors can be scrambled according to ECMA-130 Annex B") {
    int file_number = GENERATE(range(1, 11));
    // load each input and output data file, reading in their contents
    std::ifstream input_file, output_file;
    std::stringstream input_name, output_name;
    input_name << "../tests/scrambling_test_fixtures/test_"
               << std::setfill('0') << std::setw(2)
               << file_number << "_input.bin";
    output_name << "../tests/scrambling_test_fixtures/test_"
               << std::setfill('0') << std::setw(2)
               << file_number << "_output.bin";
    // try and open both files
    input_file.open(
        // C++20 code currently lacking library support:
        // std::format(
        //     "scrambling_test_fixtures/test_{0:02}_input.bin", file_number
        // ),
        input_name.str(),
        std::ios::binary
    );
    output_file.open(
        // C++20 code currently lacking library support:
        // std::format(
        //     "scrambling_test_fixtures/test_{0:02}_output.bin", file_number
        // ),
        output_name.str(),
        std::ios::binary
    );
    REQUIRE(input_file.is_open());
    REQUIRE(output_file.is_open());
    Mode2Sector raw_sector;
    ScrambledSector scrambled_sector;
    // try and read them both into the corresponding data structures
    for (std::size_t i = 0; i < 2352; i++) {
        // because C++ is a strict language, need a temporary to cast bytes
        char input_temp[1], output_temp[1];
        input_file.read(input_temp, 1);
        output_file.read(output_temp, 1);
        raw_sector.bytes[i] = (Byte)input_temp[0];
        scrambled_sector.bytes[i] = (Byte)output_temp[0];
    }

    GIVEN("An unscrambled input Sector and its expected output scrambled Sector") {
        WHEN("The input Sector is passed into the scrambler") {
            // attempt to scramble the input Sector
            ScrambledSector scrambled = scrambling::scramble(raw_sector);
            THEN("A Scrambled Sector shall be returned with same contents as expected output") {
                REQUIRE(scrambled.bytes == scrambled_sector.bytes);
            }
        }
    }

    GIVEN("A scrambled input Sector and its expected output unscrambled Sector") {
        WHEN("The input Sector is passed into the unscrambler") {
            // attempt to unscramble the input Sector
            Mode2Sector unscrambled = scrambling::unscramble(scrambled_sector);
            THEN("An un-Scrambled Sector shall be returned with same contents as expected output") {
                REQUIRE(unscrambled.bytes == raw_sector.bytes);
            }
        }
    }
}
