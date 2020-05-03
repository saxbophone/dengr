#ifndef COM_SAXBOPHONE_DENGR_SCRAMBLING
#define COM_SAXBOPHONE_DENGR_SCRAMBLING

#include <array>
#include <exception>
#include <map>

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
