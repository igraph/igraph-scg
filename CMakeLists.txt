# Minimum CMake that we require is 3.18 because igraph itself requires 3.18
# as well
cmake_minimum_required(VERSION 3.18)

# Add etc/cmake to CMake's search path so we can put our private stuff there
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/etc/cmake)

# Set a default build type if none was specified
# This must precede the project() line, which would set the CMAKE_BUILD_TYPE
# to 'Debug' with single-config generators on Windows.
# Note that we must do this only if PROJECT_NAME is not set at this point. If
# it is set, it means that igraph-scg is being used as a subproject of another
# project.
if(NOT PROJECT_NAME)
  include(BuildType)
endif()

# Make use of ccache if it is present on the host system -- unless explicitly
# asked to disable it
include(UseCCacheWhenInstalled)

# Declare the version number
include(version)

# Declare the project, its version number and language
project(
  igraph-scg
  VERSION ${PACKAGE_VERSION_BASE}
  DESCRIPTION "Spectral coarse graining of graphs"
  LANGUAGES C CXX
)

# Include some compiler-related helpers and set global compiler options
include(compilers)

# Set default symbol visibility to hidden
set(CMAKE_C_VISIBILITY_PRESET hidden)

# Set C and C++ standard version
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Expose the BUILD_SHARED_LIBS option in the ccmake UI
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Handle dependencies
find_package(igraph 1 REQUIRED)

# Enable unit tests. Behave nicely and do this only if we are not being
# included as a sub-project in another CMake project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
  configure_file(
    ${PROJECT_SOURCE_DIR}/etc/cmake/CTestCustom.cmake.in
    ${PROJECT_BINARY_DIR}/CTestCustom.cmake
  )
endif()

# Traverse subdirectories
add_subdirectory(src)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

# Configure packaging -- only if igraph-scg is the top-level project and not a
# subproject
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(packaging)
endif()

# Show result of configuration
include(summary)
