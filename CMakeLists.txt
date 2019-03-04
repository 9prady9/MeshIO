cmake_minimum_required(VERSION 3.12.3)

project(MeshIO VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if (NOT EXISTS "${MeshIO_SOURCE_DIR}/test/googletest")
  message(WARNING "google/googletest is not available. Tests will not built.")
  message("Did you miss the --recursive option when cloning?")
  message("Run the following commands to correct this:")
  message("git submodule init")
  message("git submodule update")
  message("git submodule foreach git pull origin master")
endif ()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE
      PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

option(MeshIO_BUILD_DOCS "Build Documentation" OFF)
option(MeshIO_BUILD_EXAMPLES "Build examples" OFF)
option(MeshIO_BUILD_COVERAGE "Create test coverage report" OFF)

add_library(meshio INTERFACE)

target_include_directories(meshio INTERFACE
  $<BUILD_INTERFACE:${MeshIO_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )

include(CTest)
enable_testing()
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
    "${PROJECT_SOURCE_DIR}/cmake/MeshIOConfig.cmake.in"
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

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include"
  DESTINATION .
  COMPONENT Headers
  FILES_MATCHING
  PATTERN "*.hpp"
  PATTERN "*.inl"
  )

mark_as_advanced(MeshIO_BUILD_COVERAGE)
