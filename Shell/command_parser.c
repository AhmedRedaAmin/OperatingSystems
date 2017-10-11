#include <memory.h>
#include <log_handle.h>
#include <stdlib.h>
#include <stdio.h>
#include <variables.h>
#include <unistd.h>
#include <commands.h>
#include "command_parser.h"


char ** split_command(char* command )
{
    if(strlen(command) > MAN_LENGTH){
        handle_shell_log("Command exceeds maximum length");
        exit(0);
    }

            // count tokens and initialize an array of pointers of known size;
    char** arg;
    int i = 0;
    char* token;
    tokenize(command," ",arg);
    if(arg[0] == "echo"
            && arg[1][0] == '\"'){
        i = 0;
        char *arg[3] ;
        token = strtok(command ,"\"");
        while(token != NULL){
            arg[i] = token;
            i++;
            token = strtok(NULL,"\"");
        }
        arg[i]=NULL;
        printf("%s",arg[1]);
        arg[0] = "ec";
        arg[1] = NULL;
    }


    //if echo printf
    return arg;
}

//the command can be classified as 2 things , command or variable arithmetic
//the command has 3 categories , things we must proof read , things we must implement personally
//exampel cd and echo and export , history , .. etc
//strtoc();

char** variable_processing(char** arguments){
    int y = 0;
    char* key;
    char* value;
    while(arguments[y] != NULL){
        if (arguments[y][0] == '$'){

            int z = 1;
            while(arguments[y][z] >= 97 || arguments[y][z] >= 65 || arguments[y][z] >= 48
                    || arguments[y][z] <= 90 ||arguments[y][z] <= 122 || arguments[y][z] <= 57 ||
                    arguments[y][z] == 95){
            z++;
            }
            char buffer[z+1];
            memcpy(buffer, &arguments[y][1],z);
            buffer[z+1] = '\0';
            key = buffer;
            value = lookup_variable(key);
            if (value == NULL){
            handle_shell_log("Error : no such variable");
                exit(0);
            }
            arguments[y] = value;
        } else if (arguments[y] == ".."){
            continue;
        } else if (arguments[y][0] == '.'){
            int z = 1;
            while(arguments[y][z] != '\0'){
                z++;
            }
            char buffer[z+1];
            memcpy(buffer, &arguments[y][1],z);
            buffer[z+1]= '\0';
            char* currentD = getenv("PWD");
            arguments[y] = strcat(currentD,buffer);
        }
    }
    return arguments;
}

int check_background(char ** arguments){
    char* ampersand;
    int status;
    int i = 0;
    while(arguments[i] != NULL){
        i++;
    }
    i--;
    ampersand = arguments[i];
    status = strcmp("&",ampersand);
    return status;
}


int identify_command(char** arguments){
    char* command;
    int status;
    command = arguments[0];
    int i = 0;
    while(command[i]!= '\0'){
        if(command[i] == '/' || command[i] == '~' || command[i] == '.'){
            status = EXECUTE;
            break;
        } else if (command [i] == '=' ||command == "export"){
            status = VARIABLE;
            break;
        } else{
            status = COMMAND;

        }
    i++;
    }
    return status;

}

void exec_command(char ** Arguments , int status){
    if (status == EXECUTE){
        int i = 0;
        while (Arguments[i]!= NULL){
            i++;
        }
        char *args[i+1];
        int z;
        for ( z = 0 ; z < i; z++){

            args[z] = Arguments[z];
        }
        args[z] = (char*)0;
       if (execv(args[0],args) == -1){handle_shell_log("Command failed to execute.");}
    } else if (status == VARIABLE) {
        if(Arguments[2]!= NULL){
            handle_shell_log("Variable assignment command invalid");
        } else if (Arguments[0] == "export"){


            char ** variable_assignment;
            tokenize(Arguments[1],"=",variable_assignment );
            variable_assignment = variable_processing(variable_assignment);
            set_variable(variable_assignment[0],variable_assignment[1]);
        } else {


            char ** variable_assignment;
            tokenize(Arguments[0], "=",variable_assignment);
            variable_assignment = variable_processing(variable_assignment);
            set_variable(variable_assignment[0],variable_assignment[1]);
        }


    } else {
        if(Arguments[0] == "cd"){
            cd(Arguments[1]);
        } else if (Arguments [0] == "echo"){
            int z = 2;
            char * message_buffer = Arguments[1];
            while(Arguments[z] != NULL){
                strcat(message_buffer,Arguments[z]);
                z++;
            }
            echo(message_buffer);
        } else {
            int i = 0;
            while (Arguments[i]!= NULL){
                i++;
            }
            char *args[i+1];
            int z;
            for ( z = 0 ; z < i; z++){

                args[z] = Arguments[z];
            }
            args[z] = (char*)0;
            char** path_val;

            int m = 0;
            tokenize(lookup_variable("PATH"), ":",path_val);
            int error_flag = -1 ;
            char* temp;
            while(path_val[m] != NULL && error_flag == -1 ){
                temp = strcat(path_val[m],"/");
                args[0] = strcat(temp,args[0]);
                error_flag = execv(args[0],args);
            }
            if (path_val[m] == NULL && error_flag == -1){
                handle_shell_log("Command failed to execute.");
            }
        }

    }

}

void tokenize (char * str , char * delimeter , char ** arguments){


    int i = 0;
    char* token;
    token = strtok(str , delimeter);
    while(token != NULL){
        i++;
        token = strtok(NULL,delimeter);
    }
    char *arg[i+1]  ;

    i = 0;
    token = strtok(str , delimeter);
    while(token != NULL){
        arg[i] = token;
        i++;
        token = strtok(NULL,delimeter);
    }
    arg[i]=NULL;
    arguments = arg;
}