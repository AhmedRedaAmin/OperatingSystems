cmake_minimum_required(VERSION 3.7)
project(Shell)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ${HEADER_FILES}
        command_parser.c
        commands.c
        environment.c
        file_processing.c
        linux_shell.c
        variables.c Headers/sllist.h sllist.c Headers/log_handle.h log_handle.c)

include_directories(./Headers ./Resources)
set(HEADER_FILES Headers/*)


add_executable(Shell ${SOURCE_FILES})