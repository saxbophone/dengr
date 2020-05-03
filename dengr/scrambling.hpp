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
    ScrambledSector scramble(Mode2Sector raw_sector);

    Mode2Sector unscramble(ScrambledSector scrambled_sector);
}

#endif // include guard
