Include(FetchContent)

set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.4
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests)
target_sources(tests PRIVATE eight_to_fourteen.cpp main.cpp physical_layer.cpp scrambling.cpp)
target_link_libraries(tests PRIVATE dengr-compiler-options)
target_link_libraries(tests PRIVATE dengr)
target_link_libraries(tests PRIVATE Catch2::Catch2)

enable_testing()

# auto-discover and add Catch2 tests from unit tests program
include(CTest)
include(Catch)

catch_discover_tests(tests WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")