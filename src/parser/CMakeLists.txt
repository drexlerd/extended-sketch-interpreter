file(GLOB SRC_FILES "*.cpp" "common/*.cpp" "stage_1_ast/*.cpp" "stage_2_sketch/*.cpp")
add_library(parser STATIC ${SRC_FILES})
target_link_libraries(parser formalism extended_sketch)
