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

#include <cstdint>
#include <cstddef>

#include "Byte.hpp"
#include "Mode2Sector.hpp"
#include "ScrambledSector.hpp"
#include "scrambling/scrambling.hpp"


// using unnamed namespace here to keep the ScramblerLookupTable class internal
namespace {
    using namespace com::saxbophone::dengr;

    /**
     * internal-only helper class, provides lookup table computed on construction
     * WARN: The constexpr initialisation in the constructor relies on new
     * features in the C++20 standard revision, which are only supported by
     * pre-releases of the bleeding-edge GCC-10 compiler toolchain. This allows
     * the constructor (and hence, the lookup table) to be evaluated at compile
     * time, which is really handy as the table sequence, while unwieldily
     * generated, is a deterministic sequence. This allows us to keep the best
     * of both worlds, efficiency of execution and human-readability of the code
     */
    class ScramblerLookupTable {
    public:
        /*
         * this is the default constructor. it computes the scrambling table
         * according to ECMA-130, Annex B.
         */
        constexpr ScramblerLookupTable()
          : lookup_table()
          {
            /*
             * this algorithm is based on that used in joshua_saxby_scrambler()
             * within the Python script 'ecma_130_annex_b_scrambler.py'
             *
             * That algorithm respectively is based partly on commentary
             * and analysis from Kris Kaspersky's book, "CD Cracking Uncovered:
             * Protection against unsanctioned copying", and also based on my
             * interpretation of the ECMA-130 Annex B scrambler description.
             *
             * This implementation may be slightly less efficient than Kris' but
             * it is inherently more readable.
             */
            // 16-bit shift register as specified in the standard
            std::uint16_t shift_register = 0b1000000000000001;
            // NOTE: the scrambler follows-little-endian ordering!
            this->lookup_table[0] = 0b00000001;
            this->lookup_table[1] = 0b10000000;
            // first iteration done, now the remaining 1169 iterations...
            for (std::size_t i = 1; i < 1170; i++) { // 1170 = 2340 / 12
                // XOR the register with a copy of itself shifted one right
                std::uint16_t copy = shift_register >> 1;
                shift_register ^= copy;
                // shift the result to the right again
                shift_register >>= 1;
                // there is a "bit clock", it's the XOR of the least two bits
                bool bit_clock = (
                    ((shift_register & 0b10) >> 1) ^ (shift_register & 0b1)
                );
                // the most significant bit is set to the value of the bit clock
                if (bit_clock) {
                    shift_register |= 0b1000000000000000; // set MSB 'ON'
                } else {
                    shift_register &= 0b0111111111111111; // set MSB 'OFF'
                }
                /*
                 * Kris Kaspersky claims that if the first bit (LSB) is set to
                 * 1, we should toggle the second MSB (bit right of MSB)
                 * The following if block does this, and it DOES cause the
                 * output of this implementation to produce sequences identical
                 * to other third party produced sequences, but it is not clear
                 * yet how this relates to the reference material,
                 * ECMA-130 Annex B. The other implementations might be mistaken
                 */
                if (shift_register & 0b0000000000000001) { // LSB set?
                    // flip second-most-significant bit
                    shift_register ^= 0b0100000000000000;
                }
                /*
                 * finally, split the shift register in two and pop the two
                 * halves into the lookup table, little-endian ordering
                 */
                this->lookup_table[i * 2] = (shift_register & 0x00FF);
                this->lookup_table[i * 2 + 1] = (shift_register >> 8);
            }
        }

        /*
         * overloaded [] operator allows access of the lookup table
         * Don't call it with out-of-bounds indexes.
         */
        const Byte& operator[](std::size_t i) const {
            return this->lookup_table[i];
        }

    private:
        /*
         * the lookup table has 2340 bytes because first twelve sector bytes
         * are not scrambled
         */
        std::array<Byte, 2340> lookup_table;
    };

    /*
     * this is the single lookup table instance for scrambling
     * it is initialised at compile-time (forced by the constexpr qualifier,
     * although even without the qualifier, it probably would be initialised at
     * compile time but this is not required).
     */
    static constexpr ScramblerLookupTable LOOKUP_TABLE;

    /*
     * Internal helper function for scrambling/unscrambling.
     * This reduces code duplication, as the process is completely symmetric,
     * only the input/output types differing slightly.
     */
    void scramble_unscramble(const Mode2Sector& input, Mode2Sector& output) {
        // first twelve bytes are copied verbatim
        for (std::size_t i = 0; i < 12; i++) {
            output.bytes[i] = input.bytes[i];
        }
        // bytes can be (un)scrambled by XOR'ing them with the lookup table
        for (std::size_t i = 12; i < 2352; i++) {
            output.bytes[i] = input.bytes[i] ^ LOOKUP_TABLE[i - 12];
        }
    }
}

namespace com::saxbophone::dengr::scrambling {
    ScrambledSector scramble(Mode2Sector raw_sector) {
        ScrambledSector scrambled_sector;
        scramble_unscramble(raw_sector, scrambled_sector);
        return scrambled_sector;
    }

    Mode2Sector unscramble(ScrambledSector scrambled_sector) {
        Mode2Sector unscrambled_sector;
        scramble_unscramble(scrambled_sector, unscrambled_sector);
        return unscrambled_sector;
    }
}
