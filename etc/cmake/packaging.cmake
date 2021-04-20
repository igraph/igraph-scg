set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "igraph spectral coarse graining library")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://igraph.org")
set(CPACK_PACKAGE_VENDOR "The igraph development team")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")

# Alias "dist" to "package_source"
add_custom_target(dist
  COMMAND "${CMAKE_COMMAND}"
    --build "${CMAKE_BINARY_DIR}"
    --target package_source
  VERBATIM
  USES_TERMINAL
)

#############################################################################
## Configuration of the source package
#############################################################################

# Set source package name and format
set(CPACK_SOURCE_PACKAGE_FILE_NAME "igraph-scg-${CMAKE_PROJECT_VERSION}")
set(CPACK_SOURCE_GENERATOR "TGZ")

# Declare what to include in the source tarball. Unfortunately we can only
# declare full directories here, not individual files.
set(
    CPACK_SOURCE_INSTALLED_DIRECTORIES
    "${CMAKE_SOURCE_DIR}/etc/cmake;/etc/cmake"
    "${CMAKE_SOURCE_DIR}/include;/include"
    "${CMAKE_SOURCE_DIR}/src;/src"
    "${CMAKE_SOURCE_DIR}/tests;/tests"
)

# CPack is pretty dumb as it can only copy full directories (sans the ignored
# files) to the target tarball by default. In some cases it is easier to
# whitelist files to be copied; we use CPACK_INSTALL_SCRIPT for that.
set(CPACK_INSTALL_SCRIPT "${CMAKE_SOURCE_DIR}/etc/cmake/cpack_install_script.cmake")

# Ignore the build and all hidden folders
set(
    CPACK_SOURCE_IGNORE_FILES
    "\\\\..*/"
    "\\\\.l$"
    "\\\\.y$"
    "${CMAKE_SOURCE_DIR}/build"
)

#############################################################################
## Now we can include CPack
#############################################################################

include(CPack)

