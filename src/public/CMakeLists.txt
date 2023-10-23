
# ----
# BRFS
# ----
add_executable(brfs brfs.cpp utils.cpp)
set_property(TARGET brfs PROPERTY CXX_STANDARD 17)
target_link_libraries(brfs pddl)
target_link_libraries(brfs planners)


# --
# IW
# --
add_executable(iw iw.cpp utils.cpp)
set_property(TARGET iw PROPERTY CXX_STANDARD 17)
target_link_libraries(iw dlplannovelty)
target_link_libraries(iw pddl)
target_link_libraries(iw planners)


# ---
# SIW
# ---
add_executable(siw siw.cpp utils.cpp)
set_property(TARGET siw PROPERTY CXX_STANDARD 17)
target_link_libraries(siw dlplannovelty)
target_link_libraries(siw pddl)
target_link_libraries(siw planners)

# ---
# IWR
# ---
add_executable(iwr iwr.cpp utils.cpp)
set_property(TARGET iwr PROPERTY CXX_STANDARD 17)
target_link_libraries(iwr dlplannovelty)
target_link_libraries(iwr pddl)
target_link_libraries(iwr planners)


# ---
# SIWR
# ---
add_executable(siwr siwr.cpp utils.cpp)
set_property(TARGET siwr PROPERTY CXX_STANDARD 17)
target_link_libraries(siwr dlplannovelty)
target_link_libraries(siwr pddl)
target_link_libraries(siwr planners)


add_executable(tg tuple_graph.cpp utils.cpp)
set_property(TARGET tg PROPERTY CXX_STANDARD 17)
target_link_libraries(tg dlplannovelty)
target_link_libraries(tg pddl)