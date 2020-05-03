#include <array>
#include <cstdint>

#include "Byte.hpp"
#include "Mode2Sector.hpp"
#include "ScrambledSector.hpp"
#include "scrambling.hpp"


// using unnamed namespace here to keep the ScramblerLookupTable class internal
namespace {
    using namespace com::saxbophone::dengr;

    class ScramblerLookupTable {
    public:
        // this is the default constructor. it computes the scrambling table
        ScramblerLookupTable() {
            // TODO: initialise the lookup table!
        }

        /*
         * overloaded [] operator allows access of the lookup table
         * Don't call it with out-of-bounds indexes.
         */
        const Byte& operator[](std::size_t i) const {
            return this->lookup_table[i];
        }

    private:
        std::array<Byte, 2352> lookup_table;
    };
}

namespace com::saxbophone::dengr::scrambling {
    // this is the single lookup table instance for scrambling
    static const ScramblerLookupTable LOOKUP_TABLE;

    ScrambledSector scramble(Mode2Sector raw_sector) {
        ScrambledSector scrambled_sector;
        // bytes can be scrambled by XOR'ing them with the lookup table
        for (std::size_t i = 0; i < 2352; i++) {
            scrambled_sector.bytes[i] = raw_sector.bytes[i] ^ LOOKUP_TABLE[i];
        }
        return scrambled_sector;
    }

    Mode2Sector unscramble(ScrambledSector scrambled_sector) {
        Mode2Sector unscrambled_sector;
        // bytes can be unscrambled by XOR'ing them with the lookup table
        for (std::size_t i = 0; i < 2352; i++) {
            unscrambled_sector.bytes[i] = scrambled_sector.bytes[i] ^ LOOKUP_TABLE[i];
        }
        return unscrambled_sector;
    }
}
