#ifndef COM_SAXBOPHONE_DENGR_EIGHT_TO_FOURTEEN_MODULATOR
#define COM_SAXBOPHONE_DENGR_EIGHT_TO_FOURTEEN_MODULATOR

#include <array>
#include <exception>
#include <map>

#include "Byte.hpp"
#include "ChannelByte.hpp"


namespace com::saxbophone::dengr {
    /**
     * @brief Thrown when attempting to decode a value that is not an EFM code.
     */
    class InvalidEFMCodewordException : public std::exception {
        const char* what() const noexcept {
            return "Not a valid 14-bit EFM code";
        }
    };

    /**
     * @brief Provides methods to encode to and from 8 to 14 modulation code
     * @details This implements encoding of 8-bit bytes to and from 14-bit
     * EFM codes as defined by Annex D of ECMA-130
     */
    class EightToFourteenModulator {
    public:
        /**
         * @brief Encodes 8-bit bytes into 14-bit EFM codewords
         * @param byte the 8-bit byte to encode into EFM
         * @returns 14-bit EFM codeword for the given 8-bit input byte
         */
        static ChannelByte encode(Byte byte);

        /**
         * @brief Decodes valid 14-bit EFM codewords into 8-bit bytes
         * @param efm_codeword 14-bit EFM codeword to decode into a byte
         * @returns 8-bit byte for the given 14-bit EFM codeword (if valid)
         * @throws InvalidEFMCodewordException if efm_codeword is not a valid
         * 14-bit EFM codeword
         */
        static Byte decode(ChannelByte efm_codeword);

    private:
        /**
         * @brief Lookup table used to encode 8-bit bytes into 14-bit EFM codes
         */
        static const std::array<ChannelByte, 256> ENCODING_TABLE;
        /**
         * @brief Lookup table used to decode 14-bit EFM codes back into 8-bit
         * bytes
         */
        static const std::map<ChannelByte, Byte> DECODING_TABLE;
    };
}

#endif // include guard
