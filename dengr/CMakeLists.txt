# C++ library source files
set(
    DENGR_SOURCES
    "src/ChannelFrame.cpp"
)

add_library(dengr SHARED)
target_sources(dengr PRIVATE ${DENGR_SOURCES})

add_subdirectory(src/eight_to_fourteen)
add_subdirectory(src/scrambling)

target_link_libraries(dengr PRIVATE dengr-compiler-options dengr-efm dengr-scrambling)
# set up version and soversion for the main library object
set_target_properties(
    dengr PROPERTIES
    PUBLIC_HEADER "${DENGR_HEADERS}"
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

install(
    DIRECTORY "include/" DESTINATION "include/${DENGR_PUBLIC_HEADER_DESTINATION}"
)
