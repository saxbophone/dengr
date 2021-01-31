add_library(dengr-efm OBJECT eight_to_fourteen.cpp)
set_property(TARGET dengr-efm PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(dengr-efm PRIVATE dengr-compiler-options)
