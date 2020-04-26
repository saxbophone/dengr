#include <utility>

#include <cstdint>

#include "../vendor/catch.hpp"


// XXX: stub implementation of EFM encoder for use until real one is made
uint16_t efm_encode(uint8_t byte) {
    return 0x0000;
}


SCENARIO("8-bit bytes can be converted to and from valid 14-bit EFM codewords") {
    // NOTE: this table is used both for encoding and decoding tests
    auto valid_efm_code_pair = GENERATE(
        std::pair<uint8_t, uint16_t>{0b00000000, 0b01001000100000},
        // TODO: add the whole EFM table, write a script to parse the verbatim EFM table from ECMA-130 Annex D
        std::pair<uint8_t, uint16_t>{0b00100010, 0b00001000100000}
    );
    GIVEN("An input 8-bit byte and its expected 14-bit EFM output") {
        uint8_t input = valid_efm_code_pair.first;
        uint16_t expected_output = valid_efm_code_pair.second;
        WHEN("The EFM encoder is called with the input byte as an argument") {
            uint16_t output = efm_encode(input);
            THEN("The EFM encoder should return the expected 14-bit EFM codeword") {
                REQUIRE(output == expected_output);
            }
        }
    }
}
