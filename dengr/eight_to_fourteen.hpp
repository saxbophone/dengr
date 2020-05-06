/**
 * @file
 *
 * @remarks This source file forms part of DENGR, a piece of software which
 * produces disc images which produce visible images on the recording side when
 * burned to Compact Disc.
 *
 * @author Joshua Saxby <joshua.a.saxby@gmail.com>
 * @date 2020
 *
 * @copyright Copyright (C) 2020 Joshua Saxby
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * @copyright
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * @copyright
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
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
