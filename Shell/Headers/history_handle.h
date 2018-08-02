//
// Created by ahmed on 6/26/18.
//

#include <stdio.h>

#ifndef SHELL_HISTORY_HANDLE_H
#define SHELL_HISTORY_HANDLE_H

static FILE* history_file;

void prepare_history_file();

void write_to_history(char* line);

void display_history();

#endif //SHELL_HISTORY_HANDLE_H
