cmake_minimum_required(VERSION 3.13)

##############################################################
# Language setup
##############################################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

##############################################################
# Establish project
##############################################################

project(sketches VERSION 0.1 LANGUAGES C CXX)

# Compilation flags, some configuration-specific
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic -fPIC")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS_DEBUG "-O3 -DDEBUG")

# Set a default build type if none was specified
set(default_build_type "Debug")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}', as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
endif()

option(ENABLE_TESTING "Enables compilation of tests." OFF)
if (ENABLE_TESTING)
    message("Building tests enabled.")
else()
    message("Building tests disabled.")
endif()

##############################################################
# CMake modules and macro files
##############################################################

# make cache variables for install destinations
include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH
  "${PROJECT_SOURCE_DIR}/cmake"
)
include("configure_boost")
include("configure_ccache")

# CCache
configure_ccache()

# Boost
# Find Boost headers only according to https://cmake.org/cmake/help/latest/module/FindBoost.html
configure_boost()
find_package(Boost ${BOOST_MIN_VERSION} REQUIRED PATHS ${CMAKE_PREFIX_PATH} NO_DEFAULT_PATH)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  message(STATUS "Found Boost: ${Boost_DIR} (found version ${Boost_VERSION})")
endif()

##############################################################
# Add library and executable targets
##############################################################

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

#if (ENABLE_TESTING)
#    add_subdirectory(tests)
#endif()

###########
# Install #
###########

# Install cmake scripts
install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/sketches"
)
