# Generate public header files installation subdirectory name
set(DENGR_PUBLIC_HEADER_DESTINATION "dengr")

# top-level namespace C++ library source files
set(
    DENGR_SOURCES
    "src/ChannelFrame.cpp"
)
add_library(dengr STATIC)
target_sources(dengr PRIVATE ${DENGR_SOURCES})
# library public header files location
target_include_directories(
    dengr PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/dengr/include>
    $<INSTALL_INTERFACE:include/${DENGR_PUBLIC_HEADER_DESTINATION}>  # <prefix>/include/<$DENGR_PUBLIC_HEADER_DESTINATION>
)
# pass in version of project as preprocessor definitions
target_compile_definitions(
    dengr PRIVATE
    -DDENGR_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    -DDENGR_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    -DDENGR_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    -DDENGR_VERSION_STRING=${DENGR_ESCAPED_VERSION_STRING}
)
# set up version and soversion for the main library object
set_target_properties(
    dengr PROPERTIES
    VERSION ${DENGR_VERSION_STRING}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
# inherit common project compiler options
target_link_libraries(dengr PRIVATE dengr-compiler-options)
# sources for sub-namespaces of the library
add_subdirectory(src/eight_to_fourteen)
add_subdirectory(src/scrambling)
install(
    TARGETS dengr
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(
    DIRECTORY "include/" DESTINATION "include/${DENGR_PUBLIC_HEADER_DESTINATION}"
)

# C++ program source file
set(DENGR_CLI_SOURCE "main.cpp")
# the dengr executable --this is the command-line program
add_executable(dengr-cli ${DENGR_CLI_SOURCE})
# link the program with the library and compiler options target
target_link_libraries(dengr-cli PRIVATE dengr-compiler-options dengr)
# set output name property so it will be called dengr despite target name being different
set_target_properties(dengr-cli PROPERTIES OUTPUT_NAME dengr)
install(
    TARGETS dengr-cli
    RUNTIME DESTINATION bin
)
