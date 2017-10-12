#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <variables.h>
#include <command_parser.h>
#include <memory.h>
#include <wchar.h>
#include "environment.h"
#include "file_processing.h"
#include "log_handle.h"

typedef enum{ false = 0 , true = 1 } bool ;

void kill_process(int signal);
void start(bool read_from_file);
void shell_loop(bool input_from_file,FILE* file_p);
char* path;
static pid_t  active_process;


int main(int argc, char *argv[])
{

    setup_environment();
    signal(SIGCHLD, handle_signal_shell_log);
    signal(SIGINT, kill_process);
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
{   char* x = getenv("HOME");
    chdir(x);

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
{   FILE* file_p = file_pointer;
    bool from_file = input_from_file;
    bool background;
    char* temp = getenv("PWD");
    char copy[strlen(temp)];
    strcpy(copy , temp);
    char* history = strcat(copy ,"/Resources/History.txt");
    prepare_logs();
    FILE* Historyfile = open_history_file(history,"a");
    while(true){
        char* line;
        if(from_file){
            line = get_commands_batch_file(file_p);
            if(line == NULL){
                from_file = false ;
                close_commands_batch_file(file_p);
            }
			// if end of file {from_file = false; continue;}
		}
		else{
			printf("InteractiveShell>>");
            line = malloc(520*sizeof(char));
            fgets(line,520,stdin);//read next instruction from console
            if(line == NULL){ break ;}
		}
        write_to_history_file(Historyfile,line);
        if (strlen(line) > 512 ){
            handle_shell_log("Command exceeds maximum limit");
            continue;
        }
        //parse your command here
        char temp[strlen(line)];
        memcpy(temp , &line[0],strlen(line)-1);
        temp[strlen(line)-1] = '\0';
        free(line);
        line = temp ;
        char ** context;
        context = split_command(line); //all special cases need to abort without further computations
        if(!strcmp(context[0], "history")){
            close_history_file(Historyfile);
            Historyfile = open_history_file(history,"r");
            display_history_file(Historyfile);
            close_history_file(Historyfile);
            Historyfile = open_history_file(history,"a");
            continue;
        }
        if(!strcmp(context[0],"ec") && context[1] == NULL){ continue;}
        if(!strcmp(context[0], " ")|| context[0] == NULL){ continue;}
        if(!strcmp(context[0],"exit") && from_file == false){ break;}
        if(!strcmp(context[0],"exit")){ from_file = false ; continue;}
        int nature_of_command = identify_command(context);
        context = variable_processing(context);
        if(!strcmp(context[0], "cd")) {
            exec_command(context,nature_of_command);
            continue;}  // end of special cases

        //execute your command here
        int wStatus;
        background = check_background(context) == 0 ? true : false;
        pid_t pID = fork();
        if(pID == -1){
            handle_shell_log("Forking has failed");
            continue;
        } else if(pID == 0) {
            exec_command(context,nature_of_command);
        } else {
            active_process = pID;
            //handling background and foreground ops , foreground requires parent to wait
            //for the child process to finish and return its finishing status.
            if(background == false) {
                wait(&wStatus);
                char* x = "Child of process";
                int y = getpid();
                char* z = "has terminated";
                strcat(x,(char*)(intptr_t)y);
                strcat(x,z);
                handle_shell_log(x);
                //handle Signal
            }
        }
        free(line);
        free(context);

		/*
			you don't need to write all logic here, a better practice is to call functions,
			each one contains a coherent set of logical instructions
		*/
	}
    close_history_file(Historyfile);
    free_variables_table();
}

void kill_process(int signal){
    if(kill(active_process,0) == 0){
        char* message = "Aborting active process.";
        fputs(message,stdout);
        kill(active_process, SIGKILL);
    }
}
