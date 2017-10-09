#include <unistd.h>
#include <variables.h>
#include <memory.h>
#include <log_handle.h>
#include "commands.h"


void cd( char* path )
{    char** PATH_val;
    char* token;
    int m = 0;
    token = strtok(lookup_variable("PATH") , ":");
    while(token != NULL){
        PATH_val[m] = strcat(token,'\0');
        m++;
        token = strtok(NULL,":");
    }
    PATH_val[m]=NULL;
    int error_flag = -1 ;
    m = 0;
    char* args[] = {"cd", path ,(char*)0};
    while(PATH_val[m] != NULL && error_flag == -1 ){

        error_flag = execv(strcat(PATH_val[m],"/cd"),args);
    }
    if(PATH_val[m] == NULL && error_flag == -1 ){
        handle_shell_log("Command failed to execute.");
    }

}  


void echo( char* message )
{
    char** PATH_val;
    char* token;
    int m = 0;
    token = strtok(lookup_variable("PATH") , ":");
    while(token != NULL){
        PATH_val[m] = strcat(token,'\0');
        m++;
        token = strtok(NULL,":");
    }
    PATH_val[m]=NULL;
    int error_flag = -1 ;
    m = 0;
    char* args[] = {"echo", message ,(char*)0};
    while(PATH_val[m] != NULL && error_flag == -1 ){

        error_flag = execv(strcat(PATH_val[m],"/echo"),args);
    }
    if(PATH_val[m] == NULL && error_flag == -1 ){
        handle_shell_log("Command failed to execute.");
    }
	// you should implement this function
}