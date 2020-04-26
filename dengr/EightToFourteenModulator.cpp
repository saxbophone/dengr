#include <cstdint>

#include "EightToFourteenModulator.hpp"


// TODO: Change to namespace com::saxbophone::dengr when move to C++20 complete
namespace dengr {
    // XXX: stub implementation of EFM encoder for use until real one is made
    uint16_t EightToFourteenModulator::encode(uint8_t byte) {
        return byte;
    }

    // XXX: stub implementation of EFM decoder for use until real one is made
    uint8_t EightToFourteenModulator::decode(uint16_t efm_codeword) {
        return (uint8_t)efm_codeword;
    }
}
