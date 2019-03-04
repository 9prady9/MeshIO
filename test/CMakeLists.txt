### Below code was used to verify GNU compiler
### version on travis-ci servers
if (CMAKE_COMPILER_IS_GNUCC)
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
        OUTPUT_VARIABLE GCC_VERSION)
    string(REGEX MATCHALL "[0-9]+" GCC_VERSION_COMPONENTS
        ${GCC_VERSION})
    list(GET GCC_VERSION_COMPONENTS 0 GCC_MAJOR)
    list(GET GCC_VERSION_COMPONENTS 1 GCC_MINOR)

    message(STATUS "Using GNUCC Compiler Verson ${GCC_MAJOR}.${GCC_MINOR}")
endif()

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
      FOLDER "ExternalProjectTargets/gtest")

  # Hide gtest project variables
  mark_as_advanced(
    BUILD_SHARED_LIBS
    gtest_build_samples
    gtest_build_tests
    gtest_disable_pthreads
    gtest_force_shared_crt
    gtest_hide_internal_symbols)
endif()

file(GLOB FILES "*.cpp")

foreach(FILE ${FILES})
  get_filename_component(FNAME ${FILE} NAME_WE)
  set(TEST_NAME ${FNAME})
  add_test(Test_${TEST_NAME} ${TEST_NAME})
  file(GLOB TEST_FILE "${FNAME}.cpp" "${FNAME}.c")

  add_executable(${TEST_NAME} ${TEST_FILE})

  set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 14)

  target_include_directories(${TEST_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    )

  target_compile_definitions(${TEST_NAME}
    PRIVATE
      TEST_DIR="${MeshIO_SOURCE_DIR}/resources"
    )

  target_link_libraries(${TEST_NAME}
    PRIVATE
      meshio
      gtest
      gtest_main
    )

  if (MeshIO_BUILD_COVERAGE)
    target_compile_options(${TEST_NAME}
      PRIVATE
        -g -O0 -fprofile-arcs -ftest-coverage
      )
    target_link_libraries(${TEST_NAME}
      PRIVATE
        -g -O0 -fprofile-arcs -ftest-coverage
      )
  endif (MeshIO_BUILD_COVERAGE)

  set_target_properties(${TEST_NAME} PROPERTIES FOLDER "Tests")

  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
