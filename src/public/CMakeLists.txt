add_executable(siw_r siw_r.cpp)
target_link_libraries(siw_r extended_sketch parser pddl planners dlplan::core dlplan::policy)

add_executable(siw_m siw_m.cpp)
target_link_libraries(siw_m extended_sketch parser pddl planners dlplan::core dlplan::policy)
