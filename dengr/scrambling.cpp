#include "Mode2Sector.hpp"
#include "ScrambledSector.hpp"
#include "scrambling.hpp"


namespace com::saxbophone::dengr::scrambling {
    ScrambledSector scramble(Mode2Sector raw_sector) {
        ScrambledSector scrambled_sector;
        scrambled_sector.bytes = raw_sector.bytes;
        return scrambled_sector;
    }
}
