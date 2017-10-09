#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <variables.h>
#include <command_parser.h>
#include <memory.h>
#include "environment.h"
#include "file_processing.h"
#include "log_handle.h"

typedef enum{ false = 0 , true = 1 } bool ;

void start(bool read_from_file);
void shell_loop(bool input_from_file,FILE* file_pointer);
char* path;
char* history = "./Resources/History.txt";

int main(int argc, char *argv[])
{

    setup_environment();
    signal(SIGCHLD,handle_backg_shell_log);

    // any other early configuration should be here

    if( argc == 2 ){
		path = argv[1];
        start(true);
    } else if (argc > 2) {
        handle_shell_log("Incorrect Number of Arguments to the program");
        exit(0);
    } else{
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
    bool background;
    FILE* Historyfile = open_history_file(history,"a");
	while(true){
        char* line;
        if(from_file){
            line = get_commands_batch_file(file_pointer);
            if(line == NULL){
                from_file = false ;
                close_commands_batch_file(file_pointer);
            }
			// if end of file {from_file = false; continue;}
		}
		else{
			printf("InteractiveShell>>");
            fgets(line , 520 ,stdin);//read next instruction from console
            if(line == EOF){ break ;}
		}
        write_to_history_file(Historyfile,line);
        if (strlen(line) > 512 ){
            handle_shell_log("Command exceeds maximum limit");
            continue;
        }
        //parse your command here
        char ** context;
        context = split_command(line); //all special cases need to abort without further computations
        if(context[0] == "ec" && context[1] == NULL){ continue;}
        if(context[0] == " "|| context[0] == NULL){ continue;}
        if(context[0] == "exit" && from_file == false){ break;}
        if(context[0] == "exit"){ from_file = false ; continue;}
        context = variable_processing(context); // end of special cases
        int nature_of_command = identify_command(context);


        //execute your command here
        int wStatus;
        pid_t pID = fork();
        background = check_background(context) == 0 ? true : false;
        if(pID == -1){
            handle_shell_log("Forking has failed");
            exit(0);
        } else if(pID == 0) {
            exec_command(context,nature_of_command);
        } else {
            //handling background and foreground ops , foreground requires parent to wait
            //for the child process to finish and return its finishing status.
            if(background == false) {
                wait(&wStatus);
                char* x = "Child of process";
                int y = getpid();
                char* z = "has terminated";
                strcat(x,(char*)y);
                strcat(x,z);
                handle_shell_log(x);
                //handle Signal
            }
        }


		/*
			you don't need to write all logic here, a better practice is to call functions,
			each one contains a coherent set of logical instructions
		*/
	}
    close_history_file(Historyfile);
    free_variables_table();
}

