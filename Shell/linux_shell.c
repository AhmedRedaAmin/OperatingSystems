#include <unistd.h>
#include <stdio.h>
#include "environment.h"
#include "file_processing.h"

typedef enum{ false = 0 , true = 1 } bool ;

void start_shell(bool read_from_file);
void shell_loop(bool input_from_file,FILE* file_pointer);
char* path;

int main(int argc, char *argv[])
{

    setup_environment();

    // any other early configuration should be here

    if( argc > 1 ){
		path = argv[1];
        start(true);
    }
    else{
        start(false);
    }

    return 0;
}

void start(bool read_from_file)
{
    char* home_arg[] = {"cd","~","\0"};
	execv("/bin/cd",home_arg); // let shell starts from home

	if(read_from_file){
		FILE* fp = open_commands_batch_file(path);
		// file processing functions should be called from here
		shell_loop(true,fp);
	}
	else{
		shell_loop(false,NULL);
	}
}

void shell_loop(bool input_from_file,FILE* file_pointer)
{
	bool from_file = input_from_file;

	while(true){
        char* line;
        if(from_file){
            line = get_commands_batch_file(file_pointer);
            if(line == NULL){
                from_file = false ;
            }
			// if end of file {from_file = false; continue;}
		}
		else{
			printf("InteractiveShell>>");
            fgets(line , 513 ,stdin);//read next instruction from console
		}

		//parse your command here

		//execute your command here

		/*
			you don't need to write all logic here, a better practice is to call functions,
			each one contains a coherent set of logical instructions
		*/
	}
}
