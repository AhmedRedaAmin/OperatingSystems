cmake_minimum_required(VERSION 3.7)
project(Shell)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Headers/file_processing.h
        Headers/environment.h
        Headers/commands.h
        Headers/command_parser.h
        Headers/variables.h
        command_parser.c
        commands.c
        environment.c
        file_processing.c
        linux_shell.c
        variables.c
        Headers/sllist.h
        sllist.c
        Headers/log_handle.h
        log_handle.c Headers/history_handle.h history_handle.c)

include_directories(./Headers ./Resources)
SET(CMAKE_BUILD_TYPE Debug)

add_executable(Shell ${SOURCE_FILES})