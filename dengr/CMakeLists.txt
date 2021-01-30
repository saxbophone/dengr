# C++ library source files
set(
    DENGR_SOURCES
    "src/ChannelFrame.cpp"
    "src/eight_to_fourteen.cpp"
    "src/scrambling.cpp"
)
# Header files
set(
    DENGR_HEADERS
    "include/Byte.hpp"
    "include/ChannelBit.hpp"
    "include/ChannelByte.hpp"
    "include/ChannelFrame.hpp"
    "include/dengr.hpp"
    "include/eight_to_fourteen.hpp"
    "include/F1Frame.hpp"
    "include/F2Frame.hpp"
    "include/F3Frame.hpp"
    "include/MergingBits.hpp"
    "include/Mode2Sector.hpp"
    "include/physical_layer.hpp"
    "include/physical_layer.inl"
    "include/Pit.hpp"
    "include/ScrambledSector.hpp"
    "include/scrambling.hpp"
    "include/Section.hpp"
)

# Generate rough (nearest major) version-dependent header installation folder
set(
    DENGR_ROUGH_HEADER_DESTINATION
    "dengr-${PROJECT_VERSION_MAJOR}"
)
# Generate precise (major and minor) version-dependent header installation folder
set(
    DENGR_PRECISE_HEADER_DESTINATION
    "dengr-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
)

add_library(dengr)
target_sources(dengr PRIVATE ${DENGR_SOURCES})
target_include_directories(
    dengr PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${DENGR_PRECISE_HEADER_DESTINATION}>  # <prefix>/include/dengr-<version>
)
target_link_libraries(dengr PRIVATE dengr-compiler-options)
# set up version and soversion for the main library object
set_target_properties(
    dengr PROPERTIES
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
)

# Install main library header files, both to rough and precise install locations
install(
    FILES ${DENGR_HEADERS}
    DESTINATION "include/${DENGR_ROUGH_HEADER_DESTINATION}"
)

install(
    FILES ${DENGR_HEADERS}
    DESTINATION "include/${DENGR_PRECISE_HEADER_DESTINATION}"
)
