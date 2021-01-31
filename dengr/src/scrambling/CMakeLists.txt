add_library(dengr-scrambling OBJECT scrambling.cpp)
set_property(TARGET dengr-scrambling PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(dengr-scrambling PRIVATE dengr-compiler-options)
