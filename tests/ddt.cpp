#include <utility>

#include <cstdint>

#include "../vendor/catch.hpp"


TEST_CASE("Data Generators") {
    auto pair = GENERATE(
        std::pair<uint8_t, uint16_t>{0b00000000, 0b01001000100000},
        std::pair<uint8_t, uint16_t>{0b00100010, 0b00001000100000}
    );
    REQUIRE(pair.first == pair.second);
}
