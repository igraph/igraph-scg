include(test_helpers)

# Add a compatibility alias to the "test" target so it can also be invoked as
# "make check" - for people who have it in their muscle memories from autotools
add_custom_target(build_tests)
add_custom_target(
  check
  COMMAND ${CMAKE_CTEST_COMMAND} --progress --output-on-failure -C $<CONFIG>
  COMMENT "Executing unit tests..."
  USES_TERMINAL
)
add_dependencies(check build_tests)

# Some newer gcc version have --enable-new-dtags on by default. This then leads
# to using RUNPATH instead of RPATH. Since RUNPATH is only considered after
# LD_LIBRARY_PATH, if another version of igraph-scg is installed somewhere it will
# be linked to that library.
include(CheckCCompilerFlag)
set(ORIG_CMAKE_REQUIRED_FLAGS ${CMAKE_REQUIRED_FLAGS})
set(CMAKE_REQUIRED_FLAGS "-Wl,--enable-new-dtags")
check_c_compiler_flag("" HAVE_ENABLE_NEW_DTAGS)
set(CMAKE_REQUIRED_FLAGS ${ORIG_CMAKE_REQUIRED_FLAGS})
if (HAVE_ENABLE_NEW_DTAGS AND BUILD_SHARED_LIBS)
  message(STATUS "Disabling new dtags for testing to use RPATH to ensure the correct library is found.")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--disable-new-dtags")
endif()

add_legacy_tests(
  FOLDER tests/unit NAMES
  igraph_scg_grouping
  igraph_scg_grouping2
  igraph_scg_grouping3
  igraph_scg_grouping4
  igraph_scg_semiprojectors
  igraph_scg_semiprojectors2
  igraph_scg_semiprojectors3
  scg
  scg2
  scg3
)


