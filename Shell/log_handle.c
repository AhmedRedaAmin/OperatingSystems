#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "log_handle.h"
#include "file_processing.h"

static char* Res_path;


void prepare_logs(){
    Res_path = getenv("PWD");
    char* copy = malloc(strlen(Res_path)+20);
    strcpy(copy,Res_path);
    strcat( copy , "/Resources/logs.txt");
    Res_path = copy ;
}

void handle_shell_log(char *message){
    FILE* logs = open_log_file(Res_path);
    fputs(message,logs);
    fputs(message , stdout);
    //close_log_file(logs);
}

void handle_signal_shell_log(int signal){
        char* message = "A background process has terminated.\n";
        FILE* logs = open_log_file(Res_path);
        fputs(message,logs);
        close_log_file(logs);
}