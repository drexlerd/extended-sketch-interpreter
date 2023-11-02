file(GLOB SRC_FILES "*.cpp")
add_library(search STATIC ${SRC_FILES})
target_link_libraries(search formalism planners extended_sketch)
