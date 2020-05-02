#include <array>
#include <map>

#include "Byte.hpp"
#include "ChannelByte.hpp"
#include "eight_to_fourteen.hpp"


namespace com::saxbophone::dengr::eight_to_fourteen {
    /**
     * @brief Lookup table used to encode 8-bit bytes into 14-bit EFM codes
     */
    static const std::array<ChannelByte, 256> ENCODING_TABLE = {
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
     * @brief Lookup table used to decode 14-bit EFM codes back into 8-bit
     * bytes
     */
    static const std::map<ChannelByte, Byte> DECODING_TABLE = {
        {0b01001000100000, 0b00000000},
        {0b01001000100100, 0b01000000},
        {0b10000100000000, 0b00000001},
        {0b10000100100100, 0b01000001},
        {0b10010000100000, 0b00000010},
        {0b10010000100100, 0b01000010},
        {0b10001000100000, 0b00000011},
        {0b10001000100100, 0b01000011},
        {0b01000100000000, 0b00000100},
        {0b01000100100100, 0b01000100},
        {0b00000100010000, 0b00000101},
        {0b00000000100100, 0b01000101},
        {0b00010000100000, 0b00000110},
        {0b00010000100100, 0b01000110},
        {0b00100100000000, 0b00000111},
        {0b00100100100100, 0b01000111},
        {0b01001001000000, 0b00001000},
        {0b01001001000100, 0b01001000},
        {0b10000001000000, 0b00001001},
        {0b10000001000100, 0b01001001},
        {0b10010001000000, 0b00001010},
        {0b10010001000100, 0b01001010},
        {0b10001001000000, 0b00001011},
        {0b10001001000100, 0b01001011},
        {0b01000001000000, 0b00001100},
        {0b01000001000100, 0b01001100},
        {0b00000001000000, 0b00001101},
        {0b00000001000100, 0b01001101},
        {0b00010001000000, 0b00001110},
        {0b00010001000100, 0b01001110},
        {0b00100001000000, 0b00001111},
        {0b00100001000100, 0b01001111},
        {0b10000000100000, 0b00010000},
        {0b10000000100100, 0b01010000},
        {0b10000010000000, 0b00010001},
        {0b10000010000100, 0b01010001},
        {0b10010010000000, 0b00010010},
        {0b10010010000100, 0b01010010},
        {0b00100000100000, 0b00010011},
        {0b00100000100100, 0b01010011},
        {0b01000010000000, 0b00010100},
        {0b01000010000100, 0b01010100},
        {0b00000010000000, 0b00010101},
        {0b00000010000100, 0b01010101},
        {0b00010010000000, 0b00010110},
        {0b00010010000100, 0b01010110},
        {0b00100010000000, 0b00010111},
        {0b00100010000100, 0b01010111},
        {0b01001000010000, 0b00011000},
        {0b01001000000100, 0b01011000},
        {0b10000000010000, 0b00011001},
        {0b10000000000100, 0b01011001},
        {0b10010000010000, 0b00011010},
        {0b10010000000100, 0b01011010},
        {0b10001000010000, 0b00011011},
        {0b10001000000100, 0b01011011},
        {0b01000000010000, 0b00011100},
        {0b01000000000100, 0b01011100},
        {0b00001000010000, 0b00011101},
        {0b00001000000100, 0b01011101},
        {0b00010000010000, 0b00011110},
        {0b00010000000100, 0b01011110},
        {0b00100000010000, 0b00011111},
        {0b00100000000100, 0b01011111},
        {0b00000000100000, 0b00100000},
        {0b01001000100010, 0b01100000},
        {0b10000100001000, 0b00100001},
        {0b10000100100010, 0b01100001},
        {0b00001000100000, 0b00100010},
        {0b10010000100010, 0b01100010},
        {0b00100100100000, 0b00100011},
        {0b10001000100010, 0b01100011},
        {0b01000100001000, 0b00100100},
        {0b01000100100010, 0b01100100},
        {0b00000100001000, 0b00100101},
        {0b00000000100010, 0b01100101},
        {0b01000000100000, 0b00100110},
        {0b01000000100100, 0b01100110},
        {0b00100100001000, 0b00100111},
        {0b00100100100010, 0b01100111},
        {0b01001001001000, 0b00101000},
        {0b01001001000010, 0b01101000},
        {0b10000001001000, 0b00101001},
        {0b10000001000010, 0b01101001},
        {0b10010001001000, 0b00101010},
        {0b10010001000010, 0b01101010},
        {0b10001001001000, 0b00101011},
        {0b10001001000010, 0b01101011},
        {0b01000001001000, 0b00101100},
        {0b01000001000010, 0b01101100},
        {0b00000001001000, 0b00101101},
        {0b00000001000010, 0b01101101},
        {0b00010001001000, 0b00101110},
        {0b00010001000010, 0b01101110},
        {0b00100001001000, 0b00101111},
        {0b00100001000010, 0b01101111},
        {0b00000100000000, 0b00110000},
        {0b10000000100010, 0b01110000},
        {0b10000010001000, 0b00110001},
        {0b10000010000010, 0b01110001},
        {0b10010010001000, 0b00110010},
        {0b10010010000010, 0b01110010},
        {0b10000100010000, 0b00110011},
        {0b00100000100010, 0b01110011},
        {0b01000010001000, 0b00110100},
        {0b01000010000010, 0b01110100},
        {0b00000010001000, 0b00110101},
        {0b00000010000010, 0b01110101},
        {0b00010010001000, 0b00110110},
        {0b00010010000010, 0b01110110},
        {0b00100010001000, 0b00110111},
        {0b00100010000010, 0b01110111},
        {0b01001000001000, 0b00111000},
        {0b01001000000010, 0b01111000},
        {0b10000000001000, 0b00111001},
        {0b00001001001000, 0b01111001},
        {0b10010000001000, 0b00111010},
        {0b10010000000010, 0b01111010},
        {0b10001000001000, 0b00111011},
        {0b10001000000010, 0b01111011},
        {0b01000000001000, 0b00111100},
        {0b01000000000010, 0b01111100},
        {0b00001000001000, 0b00111101},
        {0b00001000000010, 0b01111101},
        {0b00010000001000, 0b00111110},
        {0b00010000000010, 0b01111110},
        {0b00100000001000, 0b00111111},
        {0b00100000000010, 0b01111111},
        {0b01001000100001, 0b10000000},
        {0b01000100100000, 0b11000000},
        {0b10000100100001, 0b10000001},
        {0b10000100010001, 0b11000001},
        {0b10010000100001, 0b10000010},
        {0b10010010010000, 0b11000010},
        {0b10001000100001, 0b10000011},
        {0b00001000100100, 0b11000011},
        {0b01000100100001, 0b10000100},
        {0b01000100010001, 0b11000100},
        {0b00000000100001, 0b10000101},
        {0b00000100010001, 0b11000101},
        {0b00010000100001, 0b10000110},
        {0b00010010010000, 0b11000110},
        {0b00100100100001, 0b10000111},
        {0b00100100010001, 0b11000111},
        {0b01001001000001, 0b10001000},
        {0b00001001000001, 0b11001000},
        {0b10000001000001, 0b10001001},
        {0b10000100000001, 0b11001001},
        {0b10010001000001, 0b10001010},
        {0b00001001000100, 0b11001010},
        {0b10001001000001, 0b10001011},
        {0b00001001000000, 0b11001011},
        {0b01000001000001, 0b10001100},
        {0b01000100000001, 0b11001100},
        {0b00000001000001, 0b10001101},
        {0b00000100000001, 0b11001101},
        {0b00010001000001, 0b10001110},
        {0b00000010010000, 0b11001110},
        {0b00100001000001, 0b10001111},
        {0b00100100000001, 0b11001111},
        {0b10000000100001, 0b10010000},
        {0b00000100100100, 0b11010000},
        {0b10000010000001, 0b10010001},
        {0b10000010010001, 0b11010001},
        {0b10010010000001, 0b10010010},
        {0b10010010010001, 0b11010010},
        {0b00100000100001, 0b10010011},
        {0b10000100100000, 0b11010011},
        {0b01000010000001, 0b10010100},
        {0b01000010010001, 0b11010100},
        {0b00000010000001, 0b10010101},
        {0b00000010010001, 0b11010101},
        {0b00010010000001, 0b10010110},
        {0b00010010010001, 0b11010110},
        {0b00100010000001, 0b10010111},
        {0b00100010010001, 0b11010111},
        {0b01001000000001, 0b10011000},
        {0b01001000010001, 0b11011000},
        {0b10000010010000, 0b10011001},
        {0b10000000010001, 0b11011001},
        {0b10010000000001, 0b10011010},
        {0b10010000010001, 0b11011010},
        {0b10001000000001, 0b10011011},
        {0b10001000010001, 0b11011011},
        {0b01000010010000, 0b10011100},
        {0b01000000010001, 0b11011100},
        {0b00001000000001, 0b10011101},
        {0b00001000010001, 0b11011101},
        {0b00010000000001, 0b10011110},
        {0b00010000010001, 0b11011110},
        {0b00100010010000, 0b10011111},
        {0b00100000010001, 0b11011111},
        {0b00001000100001, 0b10100000},
        {0b01000100000010, 0b11100000},
        {0b10000100001001, 0b10100001},
        {0b00000100000010, 0b11100001},
        {0b01000100010000, 0b10100010},
        {0b10000100010010, 0b11100010},
        {0b00000100100001, 0b10100011},
        {0b00100100000010, 0b11100011},
        {0b01000100001001, 0b10100100},
        {0b01000100010010, 0b11100100},
        {0b00000100001001, 0b10100101},
        {0b00000100010010, 0b11100101},
        {0b01000000100001, 0b10100110},
        {0b01000000100010, 0b11100110},
        {0b00100100001001, 0b10100111},
        {0b00100100010010, 0b11100111},
        {0b01001001001001, 0b10101000},
        {0b10000100000010, 0b11101000},
        {0b10000001001001, 0b10101001},
        {0b10000100000100, 0b11101001},
        {0b10010001001001, 0b10101010},
        {0b00001001001001, 0b11101010},
        {0b10001001001001, 0b10101011},
        {0b00001001000010, 0b11101011},
        {0b01000001001001, 0b10101100},
        {0b01000100000100, 0b11101100},
        {0b00000001001001, 0b10101101},
        {0b00000100000100, 0b11101101},
        {0b00010001001001, 0b10101110},
        {0b00010000100010, 0b11101110},
        {0b00100001001001, 0b10101111},
        {0b00100100000100, 0b11101111},
        {0b00000100100000, 0b10110000},
        {0b00000100100010, 0b11110000},
        {0b10000010001001, 0b10110001},
        {0b10000010010010, 0b11110001},
        {0b10010010001001, 0b10110010},
        {0b10010010010010, 0b11110010},
        {0b00100100010000, 0b10110011},
        {0b00001000100010, 0b11110011},
        {0b01000010001001, 0b10110100},
        {0b01000010010010, 0b11110100},
        {0b00000010001001, 0b10110101},
        {0b00000010010010, 0b11110101},
        {0b00010010001001, 0b10110110},
        {0b00010010010010, 0b11110110},
        {0b00100010001001, 0b10110111},
        {0b00100010010010, 0b11110111},
        {0b01001000001001, 0b10111000},
        {0b01001000010010, 0b11111000},
        {0b10000000001001, 0b10111001},
        {0b10000000010010, 0b11111001},
        {0b10010000001001, 0b10111010},
        {0b10010000010010, 0b11111010},
        {0b10001000001001, 0b10111011},
        {0b10001000010010, 0b11111011},
        {0b01000000001001, 0b10111100},
        {0b01000000010010, 0b11111100},
        {0b00001000001001, 0b10111101},
        {0b00001000010010, 0b11111101},
        {0b00010000001001, 0b10111110},
        {0b00010000010010, 0b11111110},
        {0b00100000001001, 0b10111111},
        {0b00100000010010, 0b11111111},
    };

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
        // check that the given value is a valid efm codeword
        if (not DECODING_TABLE.contains(efm_codeword)) {
            throw InvalidEFMCodewordException();
        }
        // otherwise, we know it is a valid one so we can retrieve it
        return DECODING_TABLE.at(efm_codeword);
    }
}
