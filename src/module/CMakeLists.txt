file(GLOB SRC_FILES "*.cpp")
add_library(module STATIC ${SRC_FILES})
target_link_libraries(module extended_sketch dlplancore dlplanpolicy)
