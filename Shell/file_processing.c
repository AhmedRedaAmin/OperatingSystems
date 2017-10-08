#include <stdio.h>
#include <log_handle.h>
#include <stdint.h>
#include "file_processing.h"

//Boiler plate code is for self documenting code purposes .

/* 
	history file section
*/
FILE * open_history_file(char *string , char mode)
{
    FILE* temp = fopen(string,(char*)(intptr_t)mode);

}

void get_history_file(FILE *file)
{   char* line;
    if (file == NULL){
        handle_shell_log("An error in retrieving the file, terminating process");
        return;
    }
    while(!feof(file)){
        if (fgets (line,513,file) != NULL){
            printf("%s",line);
        }
    }
}

void write_to_history_file(FILE *file ,char* entry)
{
    fputs(entry , file);
}

void close_history_file(FILE *file)
{
    fclose(file);
}

/* 
	log file section
*/
FILE * open_log_file(char *string)
{
    FILE* temp = fopen(string,"a");
}

void write_to_log_file(FILE *file ,char* entry)
{
    fputs(entry,file);

}

void close_log_file(FILE *file)
{
    fclose(file);
}


/* 
	CommandsBatch file section
*/
FILE * open_commands_batch_file(char *string)
{
    FILE* temp = fopen(string,"r");
}

char * get_commands_batch_file(FILE *file)
{
    char* line;
    if (file == NULL){
        handle_shell_log("An error in retrieving the file, terminating process");
        return NULL;
    }

    if (!feof(file) && fgets(line,513,file) != NULL ){
        return line;
    }
    return NULL;

}

void close_commands_batch_file(FILE *file)
{
    fclose(file);
}
