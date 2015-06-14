cmake_minimum_required(VERSION 2.8)

project(MeshIO)

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()

add_executable(stl_read_test "test/stl_read_test.cpp")
