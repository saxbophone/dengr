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

// MSVC doesn't support the alternative operators out of the box
#ifdef _MSC_VER
#include <iso646.h>
#endif

#include "Byte.hpp"
#include "ChannelByte.hpp"
#include "eight_to_fourteen.hpp"


// using unnamed namespace here to keep the DecoderLookupTable class internal
namespace {
    using namespace com::saxbophone::dengr;

    /*
     * this is a dependent internal struct for DecoderLookupTable and its users
     * It provides a very simple implementation of the basic functionality
     * provided by std::optional, which cannot be used here because that type is
     * not constexpr-correct for the usage required here (we want the lookup
     * table to be generated at compile-time).
     */
    struct PresentByte {
        constexpr PresentByte()
          : is_present(false)
          , value(0)
          {}
        bool is_present; // if false, consider this value to be 'null'
        Byte value; // the value stored, to be ignored if is_present is false
    };

    /*
     * internal helper class allowing the decoder lookup table to be generated
     * at compile time, computed from the encoder lookup table
     * this implementation uses a flat array to store the lookup table with the
     * 14-bit EFM codeword as the index, which is a bit wasteful of memory as
     * most of the 14-bit combinations do not have a corresponding entry in the
     * table (table only maps to 256 values). However, it is straightforward and
     * probably very fast, as the array is effectively static and constant.
     */
    class DecoderLookupTable {
    public:
        /*
         * constructor requires the encoder lookup table to passed in, this is
         * read from to construct the decoder lookup table
         */
        constexpr DecoderLookupTable(
            const std::array<ChannelByte, 256> encoding_table
        ) {
            // construct decode table from inverse of encode table
            for (std::size_t i = 0; i < 256; i++) {
                // all zero-initialised elements will have is_present set to false
                this->lookup_table[encoding_table[i]].is_present = true;
                this->lookup_table[encoding_table[i]].value = (std::uint8_t)i;
            }
        }

        /*
         * overloaded [] operator allows access of the lookup table
         * When called with out-of-bounds indexes, it returns a 'null'
         * PresentByte
         */
        const PresentByte& operator[](std::size_t i) const {
            /*
             * in this case, element #0 is our 'null' element since we know it's
             * empty, as EFM bit pattern 0 is not valid
             */
            return i < this->lookup_table.size() ? this->lookup_table[i]
                                                 : this->lookup_table[0];
        }

    private:
        /**
         * the lookup table itself. This size of this is set to 0b10010010010010
         * plus one because 0b10010010010010 is the largest 14-bit EFM codeword
         * by decimal value and because these values are used as indices into
         * the lookup table, the table's size needs to be one greater than this
         * value to ensure it is a valid index.
         */
        std::array<PresentByte, 0b10010010010010 + 1> lookup_table;
    };
}

namespace com::saxbophone::dengr::eight_to_fourteen {
    /**
     * @brief Lookup table used to encode 8-bit bytes into 14-bit EFM codes
     */
    static constexpr std::array<ChannelByte, 256> ENCODING_TABLE = {
        0b01001000100000,
        0b10000100000000,
        0b10010000100000,
        0b10001000100000,
        0b01000100000000,
        0b00000100010000,
        0b00010000100000,
        0b00100100000000,
        0b01001001000000,
        0b10000001000000,
        0b10010001000000,
        0b10001001000000,
        0b01000001000000,
        0b00000001000000,
        0b00010001000000,
        0b00100001000000,
        0b10000000100000,
        0b10000010000000,
        0b10010010000000,
        0b00100000100000,
        0b01000010000000,
        0b00000010000000,
        0b00010010000000,
        0b00100010000000,
        0b01001000010000,
        0b10000000010000,
        0b10010000010000,
        0b10001000010000,
        0b01000000010000,
        0b00001000010000,
        0b00010000010000,
        0b00100000010000,
        0b00000000100000,
        0b10000100001000,
        0b00001000100000,
        0b00100100100000,
        0b01000100001000,
        0b00000100001000,
        0b01000000100000,
        0b00100100001000,
        0b01001001001000,
        0b10000001001000,
        0b10010001001000,
        0b10001001001000,
        0b01000001001000,
        0b00000001001000,
        0b00010001001000,
        0b00100001001000,
        0b00000100000000,
        0b10000010001000,
        0b10010010001000,
        0b10000100010000,
        0b01000010001000,
        0b00000010001000,
        0b00010010001000,
        0b00100010001000,
        0b01001000001000,
        0b10000000001000,
        0b10010000001000,
        0b10001000001000,
        0b01000000001000,
        0b00001000001000,
        0b00010000001000,
        0b00100000001000,
        0b01001000100100,
        0b10000100100100,
        0b10010000100100,
        0b10001000100100,
        0b01000100100100,
        0b00000000100100,
        0b00010000100100,
        0b00100100100100,
        0b01001001000100,
        0b10000001000100,
        0b10010001000100,
        0b10001001000100,
        0b01000001000100,
        0b00000001000100,
        0b00010001000100,
        0b00100001000100,
        0b10000000100100,
        0b10000010000100,
        0b10010010000100,
        0b00100000100100,
        0b01000010000100,
        0b00000010000100,
        0b00010010000100,
        0b00100010000100,
        0b01001000000100,
        0b10000000000100,
        0b10010000000100,
        0b10001000000100,
        0b01000000000100,
        0b00001000000100,
        0b00010000000100,
        0b00100000000100,
        0b01001000100010,
        0b10000100100010,
        0b10010000100010,
        0b10001000100010,
        0b01000100100010,
        0b00000000100010,
        0b01000000100100,
        0b00100100100010,
        0b01001001000010,
        0b10000001000010,
        0b10010001000010,
        0b10001001000010,
        0b01000001000010,
        0b00000001000010,
        0b00010001000010,
        0b00100001000010,
        0b10000000100010,
        0b10000010000010,
        0b10010010000010,
        0b00100000100010,
        0b01000010000010,
        0b00000010000010,
        0b00010010000010,
        0b00100010000010,
        0b01001000000010,
        0b00001001001000,
        0b10010000000010,
        0b10001000000010,
        0b01000000000010,
        0b00001000000010,
        0b00010000000010,
        0b00100000000010,
        0b01001000100001,
        0b10000100100001,
        0b10010000100001,
        0b10001000100001,
        0b01000100100001,
        0b00000000100001,
        0b00010000100001,
        0b00100100100001,
        0b01001001000001,
        0b10000001000001,
        0b10010001000001,
        0b10001001000001,
        0b01000001000001,
        0b00000001000001,
        0b00010001000001,
        0b00100001000001,
        0b10000000100001,
        0b10000010000001,
        0b10010010000001,
        0b00100000100001,
        0b01000010000001,
        0b00000010000001,
        0b00010010000001,
        0b00100010000001,
        0b01001000000001,
        0b10000010010000,
        0b10010000000001,
        0b10001000000001,
        0b01000010010000,
        0b00001000000001,
        0b00010000000001,
        0b00100010010000,
        0b00001000100001,
        0b10000100001001,
        0b01000100010000,
        0b00000100100001,
        0b01000100001001,
        0b00000100001001,
        0b01000000100001,
        0b00100100001001,
        0b01001001001001,
        0b10000001001001,
        0b10010001001001,
        0b10001001001001,
        0b01000001001001,
        0b00000001001001,
        0b00010001001001,
        0b00100001001001,
        0b00000100100000,
        0b10000010001001,
        0b10010010001001,
        0b00100100010000,
        0b01000010001001,
        0b00000010001001,
        0b00010010001001,
        0b00100010001001,
        0b01001000001001,
        0b10000000001001,
        0b10010000001001,
        0b10001000001001,
        0b01000000001001,
        0b00001000001001,
        0b00010000001001,
        0b00100000001001,
        0b01000100100000,
        0b10000100010001,
        0b10010010010000,
        0b00001000100100,
        0b01000100010001,
        0b00000100010001,
        0b00010010010000,
        0b00100100010001,
        0b00001001000001,
        0b10000100000001,
        0b00001001000100,
        0b00001001000000,
        0b01000100000001,
        0b00000100000001,
        0b00000010010000,
        0b00100100000001,
        0b00000100100100,
        0b10000010010001,
        0b10010010010001,
        0b10000100100000,
        0b01000010010001,
        0b00000010010001,
        0b00010010010001,
        0b00100010010001,
        0b01001000010001,
        0b10000000010001,
        0b10010000010001,
        0b10001000010001,
        0b01000000010001,
        0b00001000010001,
        0b00010000010001,
        0b00100000010001,
        0b01000100000010,
        0b00000100000010,
        0b10000100010010,
        0b00100100000010,
        0b01000100010010,
        0b00000100010010,
        0b01000000100010,
        0b00100100010010,
        0b10000100000010,
        0b10000100000100,
        0b00001001001001,
        0b00001001000010,
        0b01000100000100,
        0b00000100000100,
        0b00010000100010,
        0b00100100000100,
        0b00000100100010,
        0b10000010010010,
        0b10010010010010,
        0b00001000100010,
        0b01000010010010,
        0b00000010010010,
        0b00010010010010,
        0b00100010010010,
        0b01001000010010,
        0b10000000010010,
        0b10010000010010,
        0b10001000010010,
        0b01000000010010,
        0b00001000010010,
        0b00010000010010,
        0b00100000010010,
    };

    /**
     * @brief Lookup table used to decode 14-bit EFM codes into 8-bit bytes
     */
    static constexpr DecoderLookupTable DECODING_TABLE(ENCODING_TABLE);

    ChannelByte encode(Byte byte) {
        /*
         * NOTE: no need to use the bounds-checking interface of std::array here
         * as we can guarantee the array is big enough to handle all accesses
         * (byte is used as index)
         * HOWEVER, if byte was not 8-bit, we couldn't guarantee that an out of
         * bounds index would be passed.
         */
        return ENCODING_TABLE[byte];
    }

    Byte decode(ChannelByte efm_codeword) {
        PresentByte byte = DECODING_TABLE[efm_codeword];
        // check that the given value is a valid efm codeword
        if (not byte.is_present) { // if 'null', then it's not valid
            throw InvalidEFMCodewordException();
        }
        // otherwise, we know it is a valid one so we can return it
        return byte.value;
    }
}
