file(GLOB SRC_FILES "*.cpp" "parser/*.cpp")
add_library(extended_sketch STATIC ${SRC_FILES})
# target_link_libraries(extended_sketch dlplancore dlplanpolicy)
