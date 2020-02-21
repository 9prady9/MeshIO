cmake_minimum_required(VERSION 3.12)

project(MeshIO VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(meshioBuildType)
include(meshioChecks)

option(MeshIO_BUILD_DOCS "Build MeshIO Documentation" OFF)
option(MeshIO_BUILD_EXAMPLES "Build MeshIO Examples" OFF)
option(MeshIO_BUILD_COVERAGE "Generate MeshIO coverage report" OFF)

add_library(meshio INTERFACE)

target_include_directories(meshio INTERFACE
  $<BUILD_INTERFACE:${MeshIO_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_compile_features(meshio INTERFACE cxx_std_17)

include(CTest)
add_subdirectory(test)

if(MeshIO_BUILD_DOCS)
  add_subdirectory(docs)
endif(MeshIO_BUILD_DOCS)

if (MeshIO_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif ()

include(CMakePackageConfigHelpers)
set(INCLUDE_DIRS include)
set(CMAKE_DIR share/meshio/cmake)
configure_package_config_file(
  "${MeshIO_SOURCE_DIR}/cmake/MeshIOConfig.cmake.in"
  "cmake_install/MeshIOConfig.cmake"
  INSTALL_DESTINATION share/meshio/cmake
  PATH_VARS INCLUDE_DIRS CMAKE_DIR
)

install(TARGETS meshio EXPORT MeshIOTargets COMPONENT meshio)

install(EXPORT MeshIOTargets
  NAMESPACE MeshIO::
  DESTINATION share/meshio/cmake
  COMPONENT meshio
)

install(FILES
  ${MeshIO_BINARY_DIR}/cmake_install/MeshIOConfig.cmake
  DESTINATION share/meshio/cmake
  COMPONENT cmake
)

install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/include"
  DESTINATION .
  COMPONENT Headers
  FILES_MATCHING
  PATTERN "*.hpp"
  PATTERN "*.inl"
)

mark_as_advanced(MeshIO_BUILD_COVERAGE)
mark_as_advanced(MeshIO_BUILD_DOCS)
