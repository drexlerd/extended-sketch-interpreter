file(GLOB SRC_FILES "*.cpp" "extended_sketch/*.cpp" "formalism/*.cpp")
add_library(parsers STATIC ${SRC_FILES})
target_link_libraries(parsers formalism extended_sketch)
