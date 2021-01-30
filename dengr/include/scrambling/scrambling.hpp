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
#ifndef COM_SAXBOPHONE_DENGR_SCRAMBLING
#define COM_SAXBOPHONE_DENGR_SCRAMBLING

#include "Mode2Sector.hpp"
#include "ScrambledSector.hpp"


/**
 * @brief Functions for scrambling raw Sectors
 * @details This follows the specification in Annex B of ECMA-130.
 */
namespace com::saxbophone::dengr::scrambling {
    /**
     * @brief Scrambles the given Mode2 Raw Sector
     * @param raw_sector the Sector to scramble
     * @returns A Scrambled Sector containing the scrambled data
     */
    ScrambledSector scramble(Mode2Sector raw_sector);

    /**
     * @brief Unscrambles the given Scrambled Sector
     * @param scrambled_sector The Sector to unscramble
     * @returns A Mode 2 Sector containing the unscrambled data
     */
    Mode2Sector unscramble(ScrambledSector scrambled_sector);
}

#endif // include guard
