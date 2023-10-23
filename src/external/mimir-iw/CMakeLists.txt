cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(liw)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(default_build_type "Release")

# Retrieve the value of CMAKE_INCLUDE_PATH and split it into a list
string(REPLACE ";" " " CMAKE_INCLUDE_PATH_LIST "${CMAKE_INCLUDE_PATH}")

# Add each path in CMAKE_INCLUDE_PATH_LIST to include directories
foreach(include_dir ${CMAKE_INCLUDE_PATH_LIST})
    include_directories(${include_dir})
endforeach()

include_directories("${PROJECT_SOURCE_DIR}/src/private/dlplan")

add_subdirectory(src)

add_subdirectory(src/private/dlplan)
