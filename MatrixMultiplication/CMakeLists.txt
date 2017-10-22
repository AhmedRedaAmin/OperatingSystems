cmake_minimum_required(VERSION 3.4)
project(matMultp C CXX)

set(CMAKE_CXX_STANDARD 11)

file( GLOB SOURCE_FILES ./Headers/*.h  *.c)

find_package (Threads REQUIRED)
include_directories(./Resources ./Headers ./test)
SET(CMAKE_BUILD_TYPE Debug)

add_executable(matMultp ${SOURCE_FILES} Headers/file_processing.h Headers/methods.h Headers/struct_builder.h struct_builder.c)

target_link_libraries (matMultp ${CMAKE_THREAD_LIBS_INIT})
