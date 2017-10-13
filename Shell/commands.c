
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
//    char** PATH_val = (char**)malloc(1024*sizeof(char*));
//    int m = 0;
//    tokenize(lookup_variable("PATH"), ":",PATH_val);
//    int error_flag = -1 ;
//
//    char* args[] = {"echo", message ,(char*)0};
//    while(PATH_val[m] != NULL && error_flag == -1 ){
//        char*COPY = malloc(strlen(PATH_val[m]) + 10);
//        strcat(COPY ,PATH_val[m]);
//        strcat(COPY ,"/echo");
//        error_flag = execv(COPY,args);
//        free(COPY);
//    }
//    if(PATH_val[m] == NULL && error_flag == -1 ){
//        handle_shell_log("Command failed to execute.");
//    }
//    free(PATH_val);
}