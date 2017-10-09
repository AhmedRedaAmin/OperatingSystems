#ifndef FILE_PROCESSING_H_   /* Include guard */
#define FILE_PROCESSING_H_

/* 
	history file basic functions' prototypes
*/
FILE* open_history_file(char*,char* mode);
void get_history_file(FILE*);
void write_to_history_file(FILE *file ,char *entry);
void close_history_file(FILE*);

/* 
	log file basic functions' prototypes
*/
FILE* open_log_file(char*);
void write_to_log_file(FILE* ,char *entry);
void close_log_file(FILE*);

/* 
	CommandsBatch file basic functions' prototypes
*/
FILE* open_commands_batch_file(char*);
char* get_commands_batch_file(FILE*);
void close_commands_batch_file(FILE*);

#endif // FILE_PROCESSING_H_