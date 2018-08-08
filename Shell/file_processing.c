#include <log_handle.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>
#include <printf.h>
#include "file_processing.h"


/* 
	history file section
*/
FILE * open_history_file(char *string , char* mode)
{
    FILE* temp = fopen(string,mode);
    return temp;
}

void display_history_file(FILE *file)
{   char* line;
    line = malloc(1001);
    if (file == NULL){
        handle_shell_log("An error in retrieving the file, terminating process");
        return;
    }
    while(!feof(file)){
        fgets (line,1000,file);
            printf("%s\n",line);

    }
    free(line);
}

void write_to_history_file(FILE *file ,char* entry)
{
   int x = fputs(entry , file);
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
    FILE* temp;
    temp = fopen(string,"a");
    return temp;
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
    FILE* temp;
    temp = fopen(string,"r");
    return temp;
}

char * get_commands_batch_file(FILE *file)
{
    char* line = malloc(521);
    if (file == NULL){
        handle_shell_log("An error in retrieving the file, terminating process");
        return NULL;
    }

    if (!feof(file) && fgets(line,520,file) != NULL ){
        return line;
    }
    return NULL;

}

void close_commands_batch_file(FILE *file)
{
    fclose(file);
}
