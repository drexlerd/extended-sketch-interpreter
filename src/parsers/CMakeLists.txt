file(GLOB SRC_FILES "*.cpp"
    "common/*.cpp"
    "extended_sketch/*.cpp"
    "extended_sketch/stage_1_ast/*.cpp"
    "extended_sketch/stage_2_sketch/*.cpp")
add_library(parser STATIC ${SRC_FILES})
target_link_libraries(parser formalism extended_sketch)
