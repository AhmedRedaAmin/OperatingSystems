cmake_minimum_required(VERSION 3.4)
project(caltrain)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES caltrain-runner.c  caltrain.c caltrain.h)
find_package (Threads)
add_executable(caltrain ${SOURCE_FILES})
target_link_libraries (caltrain ${CMAKE_THREAD_LIBS_INIT})