#include <array>
#include <cstdint>

#include "Byte.hpp"
#include "Mode2Sector.hpp"
#include "ScrambledSector.hpp"
#include "scrambling.hpp"


// using unnamed namespace here to keep the ScramblerLookupTable class internal
namespace {
    using namespace com::saxbophone::dengr;

    // internal-only helper class, provides lookup table computed on construction
    class ScramblerLookupTable {
    public:
        /*
         * this is the default constructor. it computes the scrambling table
         * according to ECMA-130, Annex B.
         */
        ScramblerLookupTable() {
            /*
             * this algorithm is based on that used in joshua_saxby_scrambler()
             * within the Python script 'ecma_130_annex_b_scrambler.py'
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
}

namespace com::saxbophone::dengr::scrambling {
    /*
     * this is the single lookup table instance for scrambling
     * it is initialised at load-time
     */
    static const ScramblerLookupTable LOOKUP_TABLE;

    ScrambledSector scramble(Mode2Sector raw_sector) {
        ScrambledSector scrambled_sector;
        // first twelve bytes are copied verbatim
        for (std::size_t i = 0; i < 12; i++) {
            scrambled_sector.bytes[i] = raw_sector.bytes[i];
        }
        // bytes can be scrambled by XOR'ing them with the lookup table
        for (std::size_t i = 12; i < 2352; i++) {
            scrambled_sector.bytes[i] = raw_sector.bytes[i] ^ LOOKUP_TABLE[i - 12];
        }
        return scrambled_sector;
    }

    Mode2Sector unscramble(ScrambledSector scrambled_sector) {
        Mode2Sector unscrambled_sector;
        // first twelve bytes are copied verbatim
        for (std::size_t i = 0; i < 12; i++) {
            unscrambled_sector.bytes[i] = scrambled_sector.bytes[i];
        }
        // bytes can be unscrambled by XOR'ing them with the lookup table
        for (std::size_t i = 12; i < 2352; i++) {
            unscrambled_sector.bytes[i] = scrambled_sector.bytes[i] ^ LOOKUP_TABLE[i - 12];
        }
        return unscrambled_sector;
    }
}
