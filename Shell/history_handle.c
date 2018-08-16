//
// Created by ahmed on 6/26/18.
//
#include <file_processing.h>
#include <memory.h>
#include <stdlib.h>
#include "history_handle.h"

void prepare_history_file(){
    char* current_directory = getenv("PWD");
    char* copy= malloc(strlen(current_directory)+30);
    strcpy(copy , current_directory);
    history_file_path = strcat(copy ,"/Resources/History.txt");
    history_file = open_history_file(history_file_path,"a");
    current_mode ='a';
}

void write_to_history(char* line){
    if(current_mode != 'a'){
        close_history();
        char* temp = history_file_path ;
        history_file = open_history_file(temp ,"a");
        current_mode = 'a';
    }

    write_to_history_file(history_file,line);
}

void display_history(){

    if(current_mode != 'r'){
        close_history();
        char* temp = history_file_path;
        history_file = open_history_file(temp , "r");
        current_mode = 'r';
    }

    display_history_file(history_file);
}

void close_history(){

    close_history_file(history_file);
}
