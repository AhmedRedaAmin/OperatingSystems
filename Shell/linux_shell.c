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
    //setting up environment + catching SIGCHLD and SIGINIT from the user
    setup_environment();
    signal(SIGCHLD, handle_signal_shell_log);
    signal(SIGINT, kill_process);
    // any other early configuration should be here


    if( argc == 2 ){
		path = argv[1];
        start(true);
    } else if (argc > 2) {
        handle_shell_log("Incorrect Number of Arguments to the program \n");
        exit(0);
    } else{
        start(false);
    }

    return 0;
}

void start(bool read_from_file)
{   //start from current user home
    char* x = getenv("HOME");
    chdir(x);

	if(read_from_file){
		FILE* fp = open_commands_batch_file(path);

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
    //opening history file
    char* temp = getenv("PWD");
    char copy[strlen(temp)+30];
    strcpy(copy , temp);
    char* history = strcat(copy ,"/Resources/History.txt");
    FILE* Historyfile = open_history_file(history,"a");
    //preparing log files
    prepare_logs();
    while(true){
        char* line;
        if(from_file){
            //get instructions from file , if not return to interactive mode
            line = get_commands_batch_file(file_p);
            if(line == NULL){
                from_file = false ;
                close_commands_batch_file(file_p);
                continue;
            }
			// if end of file {from_file = false; continue;}
		}
		else{
            //interactive mode
			printf("InteractiveShell>>");
            line = malloc(520*sizeof(char));
            fgets(line,520,stdin);//read next instruction from console
            if(line == NULL){ break ;}
		}
            //every line should be admitted to history file
        write_to_history_file(Historyfile,line);
        if (strlen(line) > 512 ){
            handle_shell_log("Command exceeds maximum limit \n");
            continue;
        }
        //context is the variable containing the split arguments
        char temp[strlen(line)];
        memcpy(temp , &line[0],strlen(line)-1);
        temp[strlen(line)-1] = '\0';
        free(line);
        line = temp ;
        char ** context;
        context = split_command(line); //all special cases need to abort without further computations
        if(context[0] != NULL && !strcmp(context[0], "history")){
            close_history_file(Historyfile);
            Historyfile = open_history_file(history,"r");
            display_history_file(Historyfile);
            close_history_file(Historyfile);
            Historyfile = open_history_file(history,"a");
            continue;
        } //special cases are spread out like that for readability instead of a long AND-OR
        if(context[0] != NULL && !strcmp(context[0],"ec") && !strcmp(context[1] , "")){ continue;}
        if(context[0] != NULL && !strcmp(context[0], " ")|| context[0] == NULL){ continue;}
        if(context[0][0] == '#'){ continue;}
        if(context[0] != NULL && !strcmp(context[0],"exit") && from_file == false){ break;}
        if(context[0] != NULL && !strcmp(context[0],"exit")){ from_file = false ; continue;}
        int nature_of_command = identify_command(context);
        context = variable_processing(context);
        if(context[0] != NULL && !strcmp(context[0], "cd")) {
            exec_command(context,nature_of_command);
            continue;}// end of special cases

        //execution starts here
        int wStatus;
        background = check_background(context) == 0 ? true : false;




        pid_t pID = fork();
        if(pID == -1){
            handle_shell_log("Forking has failed \n");
            continue;
        } else if(pID == 0) {
            exec_command(context,nature_of_command);
        } else {
            active_process = pID;
            //handling background and foreground ops , foreground requires parent to wait
            //for the child process to finish and return its finishing status.
            if(background == false) {
                do{
                    waitpid(pID, &wStatus, WUNTRACED);
                }while( !WIFEXITED(wStatus) && !WIFSIGNALED(wStatus) );
                char* x = "Child of process ";
                int y = getpid();
                char* z = " has terminated \n";
                char * COPY = malloc(strlen(x)+strlen(z)+12);
                memset(COPY,0,strlen(x)+strlen(z)+12);
                strcat(COPY,x);
                char* buffer = malloc(11);
                snprintf(buffer,sizeof(buffer),"%d",y);
                strcat(COPY,buffer);
                strcat(COPY,z);
                handle_shell_log(COPY);
                free(COPY);
                free(buffer);
                //handle Signal
            }
        }


	}
    close_history_file(Historyfile);
    free_variables_table();
}
    //SIGINT handler
void kill_process(int signal){
    if(kill(active_process,0) == 0){
        char* message = "Aborting active process.\n";
        fputs(message,stdout);
        kill(active_process, SIGKILL);
    }
}
