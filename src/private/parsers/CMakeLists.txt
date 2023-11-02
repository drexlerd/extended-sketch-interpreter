file(GLOB SRC_FILES "*.cpp"
    "syntactic/*.cpp"
    "semantic/*.cpp")
add_library(parser STATIC ${SRC_FILES})
target_link_libraries(parser formalism extended_sketch)
