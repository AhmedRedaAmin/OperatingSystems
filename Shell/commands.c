#include <unistd.h>
#include <variables.h>
#include <memory.h>
#include <log_handle.h>
#include <command_parser.h>
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
    char** PATH_val;
    int m = 0;
    tokenize(lookup_variable("PATH"), ":",PATH_val);
    int error_flag = -1 ;

    char* args[] = {"echo", message ,(char*)0};
    while(PATH_val[m] != NULL && error_flag == -1 ){

        error_flag = execv(strcat(PATH_val[m],"/echo"),args);
    }
    if(PATH_val[m] == NULL && error_flag == -1 ){
        handle_shell_log("Command failed to execute.");
    }
}