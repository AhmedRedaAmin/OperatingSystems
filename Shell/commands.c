
#include <variables.h>
#include <log_handle.h>
#include <command_parser.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include "commands.h"


void cd( char* path )
{
    int error_flag;
    error_flag = chdir(path);
    if( error_flag == -1 ){
        handle_shell_log("Command failed to execute.");
    }
}  


void echo( char* message )
{
    fputs(message,stdout);
    fputs("\n",stdout);
}