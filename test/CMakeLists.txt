set(CMAKE_POLICY_DEFAULT_CMP0042 NEW)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
  gtest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0)

FetchContent_GetProperties(gtest)

if(NOT gtest_POPULATED)
  FetchContent_Populate(gtest)
  set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE BOOL "")
  add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BINARY_DIR} EXCLUDE_FROM_ALL)
  unset(CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
endif()

# Hide gtest project variables
mark_as_advanced(
  gmock_build_tests
  gtest_build_samples
  gtest_build_tests
  gtest_disable_pthreads
  gtest_force_shared_crt
  gtest_hide_internal_symbols
  BUILD_GMOCK
  BUILD_GTEST)

set_target_properties(gtest gtest_main PROPERTIES FOLDER "ExternalProjectTargets/gtest")

set(test_sources
  ${CMAKE_CURRENT_LIST_DIR}/stl.cpp
)

foreach (src ${test_sources})
  get_filename_component(FNAME ${src} NAME_WE)
  set(testTargetName ${FNAME})

  add_test(NAME ${testTargetName} COMMAND ${testTargetName})
  add_executable(${testTargetName} ${src})

  set_target_properties(${testTargetName}
    PROPERTIES
    CXX_STANDARD 17
    FOLDER "Tests"
  )
  target_include_directories(${testTargetName}
      PRIVATE ${CMAKE_CURRENT_LIST_DIR}
  )
  target_compile_definitions(${testTargetName}
    PRIVATE
      TEST_DIR="${MeshIO_SOURCE_DIR}/resources"
  )
  target_link_libraries(${testTargetName}
    PRIVATE
      meshio
      gtest
      gtest_main
  )
  if (${MeshIO_BUILD_COVERAGE})
    if (NOT UNIX)
      message(SEND_ERROR "coverage build on Windows not available now")
    endif ()
    target_compile_options(${testTargetName}
      PRIVATE
        -g -O0 -fprofile-arcs -ftest-coverage
    )
    target_link_libraries(${testTargetName}
      PRIVATE
        -g -O0 -fprofile-arcs -ftest-coverage
    )
  endif ()
endforeach ()
