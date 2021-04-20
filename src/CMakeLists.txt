add_library(
  igraph-scg

  scg_approximate_methods.c
  scg_exact_scg.c
  scg_kmeans.c
  scg_optimal_method.c
  scg_utils.c
  scg.c
)

# Set soname for the library
set_target_properties(igraph-scg PROPERTIES VERSION "0.0.0")
set_target_properties(igraph-scg PROPERTIES SOVERSION 0)

# Add include path. Includes are in ../include but they get installed to
# <prefix>/include, hence the two options. We also have some private
# includes that are generated at compile time but are not part of the public
# interface.
target_include_directories(
  igraph-scg
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# We need to link to igraph itself
target_link_libraries(igraph-scg PUBLIC igraph::igraph)

# Turn on all warnings for GCC, clang and MSVC
use_all_warnings(igraph-scg)

include(GNUInstallDirs)
include(GenerateExportHeader)
generate_export_header(igraph-scg
  STATIC_DEFINE IGRAPH_STATIC
  EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/igraph_scg_export.h
)

# Define how to install the library
install(
  TARGETS igraph-scg
  EXPORT igraph_scg_targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h"
)
install(
  DIRECTORY ${PROJECT_BINARY_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h"
)


