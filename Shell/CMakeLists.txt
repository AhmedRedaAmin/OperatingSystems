cmake_minimum_required(VERSION 3.7)
project(Shell)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Headers/command_parser.h
        Headers/commands.h
        Headers/environment.h
        Headers/file_processing.h
        Headers/variables.h
        command_parser.c
        commands.c
        environment.c
        file_processing.c
        linux_shell.c
        variables.c)

add_executable(Shell ${SOURCE_FILES})