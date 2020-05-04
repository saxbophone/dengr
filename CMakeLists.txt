# CMake project file based on Joshua Saxby's template located at
# https://gist.github.com/saxbophone/b98bc600043c1ffa95dd73843e1ea6f3#file-cmakelists-txt

# begin basic metadata
cmake_minimum_required(VERSION 3.0)

project(dengr VERSION 0.0.0 LANGUAGES CXX)

# set the C++ standard to use to C++20 always
set(DENGR_CXX_STANDARD "20")
message(STATUS "[dengr] C++ Standard set to C++${DENGR_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD ${DENGR_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    DENGR_VERSION_STRING
    "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
)
set(DENGR_ESCAPED_VERSION_STRING "\"${DENGR_VERSION_STRING}\"")
# end basic metadata

# pass in version of project as preprocessor definitions
add_definitions(-DDENGR_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DDENGR_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DDENGR_VERSION_PATCH=${PROJECT_VERSION_PATCH})
add_definitions(-DDENGR_VERSION_STRING=${DENGR_ESCAPED_VERSION_STRING})

# used for enabling additional compiler options if supported
include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    message(STATUS "[dengr] Checking if compiler supports warning flag '${flag}'")
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            message(STATUS "[dengr] Enabling warning flag '${flag}'")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
    endif()
    unset(flag_already_set CACHE)
    unset(flag_supported CACHE)
endfunction()

# enable extra flags (warnings) if we're not in release mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "[dengr] Warnings Enabled")
    # enable all warnings about 'questionable constructs'
    enable_cxx_compiler_flag_if_supported("-Wall")
    # issue 'pedantic' warnings for strict ISO compliance
    enable_cxx_compiler_flag_if_supported("-pedantic")
    # enable 'extra' strict warnings
    enable_cxx_compiler_flag_if_supported("-Wextra")
    # enable sign and type conversion warnings
    enable_cxx_compiler_flag_if_supported("-Wsign-conversion")
    # enable warnings about mistakes in Doxygen documentation
    enable_cxx_compiler_flag_if_supported("-Wdocumentation")
    # convert all warnings into errors
    enable_cxx_compiler_flag_if_supported("-Werror")
    # exclude the following kinds of warnings from being converted into errors
    # there are some pragmas in tests/check_wrapper.h that are not for GCC
    enable_cxx_compiler_flag_if_supported("-Wno-error=unknown-pragmas")
    # unused variable and function warnings are helpful but we don't need them as errors
    enable_cxx_compiler_flag_if_supported("-Wno-error=unused-function")
    enable_cxx_compiler_flag_if_supported("-Wno-error=unused-variable")
    enable_cxx_compiler_flag_if_supported("-Wno-error=unused-parameter")
endif()

# begin dependencies

# ...Add additional dependencies here...

# end dependencies

# C++ library source files
file(GLOB DENGR_SOURCES "dengr/*.cpp")
# C++ program source file
set(DENGR_CLI_SOURCE "main.cpp")
# C++ source files for unit tests
file(GLOB TEST_SOURCES "tests/*.cpp")
# Header files
set(DENGR_HEADERS "dengr/*.hpp")

# if project is a library
add_library(dengr ${DENGR_SOURCES})
# set up version for library objects
set_target_properties(
    dengr PROPERTIES VERSION ${DENGR_VERSION_STRING}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
# link DENGR with C math library
target_link_libraries(dengr m)

# the dengr executable --this is the command-line program
add_executable(dengr-cli ${DENGR_CLI_SOURCE})
# link the program with the library
target_link_libraries(dengr-cli dengr)
# set output name property so it will be called dengr despite target name being different
set_target_properties(dengr-cli PROPERTIES OUTPUT_NAME dengr)

# build unit tests
add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests dengr)
enable_testing()
add_test(unit_tests unit_tests)

install(
    TARGETS dengr
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(
    TARGETS dengr-cli
    RUNTIME DESTINATION bin
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

# Install main library header files, both to rough and precise install locations
install(
    FILES ${DENGR_HEADERS}
    DESTINATION "include/${DENGR_ROUGH_HEADER_DESTINATION}"
)

install(
    FILES ${DENGR_HEADERS}
    DESTINATION "include/${DENGR_PRECISE_HEADER_DESTINATION}"
)
