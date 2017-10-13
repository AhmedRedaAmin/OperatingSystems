#include <memory.h>
#include <log_handle.h>
#include <stdlib.h>
#include <stdio.h>
#include <variables.h>
#include <unistd.h>
#include <commands.h>
#include <pwd.h>
#include "command_parser.h"


char ** split_command(char* command )
{
    if(strlen(command) > MAN_LENGTH){
        handle_shell_log("Command exceeds maximum length \n");
        return 0;
    }


    char** arg = (char**)malloc(520*sizeof(char*));
    int i = 0;
    char* token;
    char* temp = malloc(513);
    strcpy(temp,command);
    tokenize(command," ",arg);

    if( arg[0] != NULL && !strcmp(arg[0], "echo")
            && arg[1][0] == '\"'){
        i = 0;
        char *args[3] ;
        token = strtok(temp ,"\"");
        while(token != NULL){
            args[i] = token;
            i++;
            token = strtok(NULL,"\"");
        }
        args[i]=NULL;
        printf("%s\n",args[1]);
        arg[0] = "ec";
        arg[1] = "\0";
    }

    free(temp);

    //if echo printf
    return arg;
}

    //resolving all $ ~ and .

char** variable_processing(char** arguments){
    int y = 0;
    char* key;
    char* value;
    while(arguments[y] != NULL){
        if(arguments[y][0] == '~'){
            char* home_dir;
            int z = 1,aux;
            while(arguments[y][z] != '/' && arguments[y][z] != '\0'){
                z++;
            }
            if(z > 1) {
                char user[z];
                memcpy(user, &arguments[y][1],z-1);
                user[z-1] = '\0';
                struct passwd *user_account = getpwnam(user);
                char* temp = user_account->pw_dir;
                home_dir = malloc(strlen(temp)+1);
                strcpy(home_dir,temp);
            } else {
                char* temp = getenv("HOME");
                home_dir = malloc(strlen(temp)+1);
                strcpy(home_dir,temp);
            }
            aux = z ;
            while(arguments[y][z] != '\0'){
                z++;
            }
            char buffer[z];
            memcpy(buffer, &arguments[y][aux],z-aux);
            buffer[z-aux]= '\0';
            strcat(home_dir,buffer);
            arguments[y] =home_dir;
        } else if (arguments[y][0] == '.' && arguments[y][1] == '.'){
            int z = 2;
            while(arguments[y][z] != '\0'){
                z++;
            }
            char buffer[z+1];
            memcpy(buffer, &arguments[y][2],z);
            buffer[z+1]= '\0';
            char* currentD = malloc(1024);
            getcwd(currentD,1024);
            int i = 0,last_slash = 0;
            while(currentD[i] != '\0'){
                if(currentD[i] == '/'){
                    last_slash = i;
                }
                i++;
            }
            char* temp = malloc(last_slash+1+strlen(buffer));
            memcpy(temp , &currentD[0], last_slash);
            arguments[y] = strcat(temp,buffer);
            free(currentD);
            continue;
        } else if (arguments[y][0] == '.'){
            int z = 1;
            while(arguments[y][z] != '\0'){
                z++;
            }
            char buffer[z+1];
            memcpy(buffer, &arguments[y][1],z);
            buffer[z+1]= '\0';
            char* currentD = malloc(1024);
            getcwd(currentD,1024);
            arguments[y] = strcat(currentD,buffer);
        }
        int z = 0,start_loc;
        do {
            while (arguments[y][z] != '$' && arguments[y][z] != '\0') {
                z++;
            }
            if(arguments[y][z] == '\0'){ break;}
            start_loc = z;
            z++;
            while ((arguments[y][z] >= 'a' && arguments[y][z] <= 'z')
                   ||( arguments[y][z] >= 'A'&& arguments[y][z] <= 'Z')
                   || (arguments[y][z] >= '0' && arguments[y][z] <= '9') ||arguments[y][z] == 95) {
                z++;
            }
            char buffer[z + 1];
            memcpy(buffer, &arguments[y][start_loc+1], z-start_loc-1);
            buffer[z-start_loc-1] = '\0';
            key = buffer;
            value = lookup_variable(key);
            char* rest_of_string = malloc(513);
            char start_of_string[1024];
            if(start_loc > 0) {
                char start_of_string[start_loc + 2];
                memcpy(start_of_string, &arguments[y][0], start_loc - 1);
                start_of_string[start_loc] = '\0';
            } else {
                strcpy(start_of_string,"");
            }
            memcpy(rest_of_string,&arguments[y][z],strlen(arguments[y])-z);
            rest_of_string[strlen(arguments[y])-z] = '\0';
            if (value == NULL) {
                handle_shell_log("Error : no such variable\n");
                strcat(start_of_string,"@");
                continue;
            } else{
            strcat(start_of_string,value);
            }
            strcat(start_of_string,rest_of_string);
            strcpy(arguments[y],start_of_string) ;
            free(rest_of_string);
        }while(1);
        y++;
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

    //the command can be classified as 3 things , command , execute path or variable
    //assignment .

int identify_command(char** arguments){
    char* command;
    int status;
    command = arguments[0];
    int i = 0;
    while(command[i]!= '\0'){
        if(command[i] == '/' || command[i] == '~' || command[i] == '.'){
            status = EXECUTE;
            break;
        } else if (command [i] == '=' ||!strcmp(command,"export")){
            status = VARIABLE;
            break;
        } else{
            status = COMMAND;

        }
    i++;
    }
    return status;

}

    //command execution
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
        if (execv(args[0],args) == -1){handle_shell_log("Command failed to execute.\n");}
        free(Arguments);
    } else if (status == VARIABLE) {
        if(Arguments[2]!= NULL){
            handle_shell_log("Variable assignment command invalid \n");
        } else if (!strcmp(Arguments[0], "export")){


            char ** variable_assignment = (char**)malloc(1024*sizeof(char*));
            tokenize(Arguments[1],"=",variable_assignment );
            variable_assignment = variable_processing(variable_assignment);
            set_variable(variable_assignment[0],variable_assignment[1]);
            free(variable_assignment);
        } else {

            char ** variable_assignment = (char**)malloc(1024*sizeof(char*));
            tokenize(Arguments[0], "=",variable_assignment);
            variable_assignment = variable_processing(variable_assignment);
            set_variable(variable_assignment[0],variable_assignment[1]);
            free(variable_assignment);
        }
        free(Arguments);

    } else {
        if(!strcmp(Arguments[0],"cd")){
            if(Arguments[1] == NULL){
                Arguments[1] = getenv("HOME");
            }
            cd(Arguments[1]);
        } else if (!strcmp(Arguments [0],"echo")){
            int z = 1;
            char * message_buffer = malloc(513);
            memset(message_buffer,0,513);
            while(Arguments[z] != NULL){
                strcat(message_buffer,Arguments[z]);
                z++;
            }
            echo(message_buffer);
            free(message_buffer);
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
            char** path_val = (char**)malloc(1024*sizeof(char*));

            int m = 0;
            tokenize(lookup_variable("PATH"), ":",path_val);
            int error_flag = -1 ;

            while(path_val[m] != NULL && error_flag == -1 ){
                char* temp = malloc(1024);
                memset(temp,0,1024);
                strcat(temp,path_val[m]);
                strcat(temp,"/");
                strcat(temp,args[0]);
                error_flag = execv(temp ,args);
                free(temp);
                m++;
            }
            if (path_val[m] == NULL && error_flag == -1){
                handle_shell_log("Command failed to execute.\n");
            }
            free(Arguments);
            free(path_val);
        }

    }

}

// count tokens and initialize an array of pointers of known size;
void tokenize (char * str , char * delimeter , char ** arguments){

    char* temp = malloc(strlen(str)+1);
    strcpy(temp,str);
    int i = 0;
    char* token;
    token = strtok(temp , delimeter);
    while(token != NULL){
        i++;
        token = strtok(NULL,delimeter);
    }
    char *arg[i+1]  ;

    i = 0;
    token = strtok(str , delimeter);
    while(token != NULL){
        arg[i] = malloc(strlen(token)+1);
        strcpy(arg[i] ,token);
        i++;
        token = strtok(NULL,delimeter);
    }
    arg[i]=NULL;
    i = 0;
    while(arg[i] != NULL){
        arguments[i] = arg[i];
        i++;
    }

    free(temp);

}