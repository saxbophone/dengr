#ifndef COM_SAXBOPHONE_DENGR_EIGHT_TO_FOURTEEN
#define COM_SAXBOPHONE_DENGR_EIGHT_TO_FOURTEEN

#include <array>
#include <exception>
#include <map>

#include "Byte.hpp"
#include "ChannelByte.hpp"


/**
 * @brief Functions for encoding 8-bit Bytes to and from 14-bit Channel Bytes
 * @details This follows the definition of Eight-to-Fourteen encoding as defined
 * by Annex D of ECMA-130.
 */
namespace com::saxbophone::dengr::eight_to_fourteen {
    /**
     * @brief Thrown when attempting to decode a value that is not an EFM code.
     */
    class InvalidEFMCodewordException : public std::exception {
        const char* what() const noexcept {
            return "Not a valid 14-bit EFM code";
        }
    };

    /**
     * @brief Encodes 8-bit bytes into 14-bit EFM codewords
     * @param byte the 8-bit byte to encode into EFM
     * @returns 14-bit EFM codeword for the given 8-bit input byte
     */
    ChannelByte encode(Byte byte);

    /**
     * @brief Decodes valid 14-bit EFM codewords into 8-bit bytes
     * @param efm_codeword 14-bit EFM codeword to decode into a byte
     * @returns 8-bit byte for the given 14-bit EFM codeword (if valid)
     * @throws InvalidEFMCodewordException if efm_codeword is not a valid
     * 14-bit EFM codeword
     */
    Byte decode(ChannelByte efm_codeword);
}

#endif // include guard
