# C++ library source files
set(
    DENGR_SOURCES
    "src/ChannelFrame.cpp"
)
# Header files
set(
    DENGR_HEADERS
    "include/Byte.hpp"
    "include/ChannelBit.hpp"
    "include/ChannelByte.hpp"
    "include/ChannelFrame.hpp"
    "include/dengr.hpp"
    "include/eight_to_fourteen/eight_to_fourteen.hpp"
    "include/F1Frame.hpp"
    "include/F2Frame.hpp"
    "include/F3Frame.hpp"
    "include/MergingBits.hpp"
    "include/Mode2Sector.hpp"
    "include/physical_layer/physical_layer.hpp"
    "include/physical_layer/physical_layer.inl"
    "include/Pit.hpp"
    "include/ScrambledSector.hpp"
    "include/scrambling/scrambling.hpp"
    "include/Section.hpp"
)

add_subdirectory(src/eight_to_fourteen)
add_subdirectory(src/scrambling)

add_library(dengr)
target_sources(dengr PRIVATE ${DENGR_SOURCES})
target_link_libraries(dengr PRIVATE dengr-compiler-options dengr-efm dengr-scrambling)
# set up version and soversion for the main library object
set_target_properties(
    dengr PROPERTIES
    PUBLIC_HEADER ${DENGR_HEADERS}
    VERSION ${DENGR_VERSION_STRING}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# C++ program source file
set(DENGR_CLI_SOURCE "main.cpp")

# the dengr executable --this is the command-line program
add_executable(dengr-cli ${DENGR_CLI_SOURCE})
# link the program with the library
target_link_libraries(dengr-cli PRIVATE dengr dengr-compiler-options)
# set output name property so it will be called dengr despite target name being different
set_target_properties(dengr-cli PROPERTIES OUTPUT_NAME dengr)

install(
    TARGETS dengr-cli
    RUNTIME DESTINATION bin
)

install(
    TARGETS dengr
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION "include/${DENGR_PRECISE_HEADER_DESTINATION}"
)
