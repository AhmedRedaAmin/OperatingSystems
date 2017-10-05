#include <stdio.h>
#include "log_handle.h"
#include "file_processing.h"



void handle_shell_log(char *message){
    FILE* logs = open_log_file("./Resources/logs.txt");
    fputs(message,logs);
    fputs(message , stdout);
    close_log_file(logs);
}