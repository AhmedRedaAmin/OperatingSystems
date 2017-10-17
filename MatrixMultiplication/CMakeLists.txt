cmake_minimum_required(VERSION 3.4)
project(matMultp)

set(CMAKE_CXX_STANDARD 11)

file( GLOB SOURCE_FILES ./Headers/*.h  *.c)

include_directories(./Resources ./Headers)
SET(CMAKE_BUILD_TYPE Debug)

add_executable(matMultp ${SOURCE_FILES} Headers/file_processing.h Headers/matrix_builder.h Headers/methods.h)
