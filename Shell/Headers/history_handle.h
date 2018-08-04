//
// Created by ahmed on 6/26/18.
//

#include <stdio.h>

#ifndef SHELL_HISTORY_HANDLE_H
#define SHELL_HISTORY_HANDLE_H

static char current_mode;
static FILE* history_file;
static char* history_file_path;



/** Prepares history file by constructing it's path and getting the file pointer.
 * By default the file is opened in append mode , because there is much more writes than
 * reads on average .
 */
void prepare_history_file();

/** Wrapper that writes to the history file .
 *
 * @param line
 */
void write_to_history(char* line);

/** Wrapper that reads from the history file .
 */
void display_history();

/** Wrapper for closing File stream .
 */
void close_history();

#endif //SHELL_HISTORY_HANDLE_H
