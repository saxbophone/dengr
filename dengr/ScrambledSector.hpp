#ifndef COM_SAXBOPHONE_DENGR_SCRAMBLED_SECTOR
#define COM_SAXBOPHONE_DENGR_SCRAMBLED_SECTOR

#include "Mode2Sector.hpp"


// TODO: Change to namespace com::saxbophone::dengr when move to C++20 complete
namespace dengr {
    /**
     * @brief A CD-ROM Sector that has been scrambled by the ECMA-130 Annex B
     * Scrambler.
     * @note Scrambled CD-ROM Sectors are always 2352 bytes long regardless of
     * what their Mode is.
     * @remarks Reference: ECMA-130, sec. 15
     */
    struct ScrambledSector : public Mode2Sector {};
}

#endif // include guard
