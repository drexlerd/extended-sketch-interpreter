file(GLOB SRC_FILES "*.cpp")
add_library(parser STATIC ${SRC_FILES})
# target_link_libraries(parser formalism extended_sketch)

target_compile_options(parser PRIVATE -ftemplate-backtrace-limit=0)