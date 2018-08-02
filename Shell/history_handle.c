//
// Created by ahmed on 6/26/18.
//
#include <file_processing.h>
#include <memory.h>
#include <stdlib.h>
#include "history_handle.h"

void prepare_history_file(){
    char* temp = getenv("PWD");
    char copy[strlen(temp)+30];
    strcpy(copy , temp);
    char* history = strcat(copy ,"/Resources/History.txt");
    history_file = open_history_file(history,"a");
}

void write_to_history(char* line);

void display_history();
