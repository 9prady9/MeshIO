if (NOT TARGET gtest)
  # gtest targets cmake version 2.6 which throws warnings for policy CMP0042 on
  # newer cmakes. This sets the default global setting for that policy.
  set(CMAKE_POLICY_DEFAULT_CMP0042 NEW)
  if(WIN32)
    set(gtest_force_shared_crt ON
      CACHE INTERNAL "Required so that the libs Runtime is not set to MT DLL")
  endif()

  set(GOOGLETEST_VERSION 1.8.1) #DUMMY to suppress cmake bug
  add_subdirectory(googletest/googletest EXCLUDE_FROM_ALL)
  set_target_properties(gtest gtest_main
    PROPERTIES
      FOLDER "ExternalProjectTargets/gtest"
  )

  # Hide gtest project variables
  mark_as_advanced(
    BUILD_SHARED_LIBS
    gtest_build_samples
    gtest_build_tests
    gtest_disable_pthreads
    gtest_force_shared_crt
    gtest_hide_internal_symbols)
endif ()

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
