#include "../vendor/catch.hpp"


SCENARIO("The unit testing system functions") {
    GIVEN("Two integers, a and b, a < b") {
        int a = 1;
        int b = 3;

        WHEN("The a is checked to be less than b") {
            THEN("The result of the comparison is true") {
                REQUIRE(a < b);
            }
        }
    }
}
