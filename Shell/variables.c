#include <sllist.h>
#include <stdio.h>
#include <log_handle.h>
#include <memory.h>
#include "variables.h"
#include "file_processing.h

struct sllist* variableT;

void setup_variables_table(){

    variableT = sllist_create();
    FILE* E_Variable = open_EV_file("./Resources/EnvironmentVariables");
    if(E_Variable != NULL){
        char *line;
        line = get_EV_file(E_Variable);
        while(line != NULL) {
            struct keyValuePair temp = split_variable(line);
            set_variable(temp.key,temp.data);
            line = get_EV_file(E_Variable);
        }
    } else {
        handle_shell_log("Opening the environmentVar file has failed");
    }
}
const char* lookup_variable( const char* key )
{   variableT->current = variableT->head;
    int status = variableT->current == NULL ?  1 : 6 ;
    char* value;
    while (status != 1){
        int i = 0;
        status = sllist_step(variableT);
        while(key[i]!= '\0' && variableT->current->key[i] != '\0'){
            if(key[i] != variableT->current[i].key){
                break;
            }
            i++;
        }
        if( key[i] == '\0' && variableT->current->key[i] == '\0'){
        value = variableT->current->data;
            break;
        }
    }
    variableT->current = variableT->head;
    return value;

}

void set_variable( const char* key , const char* value )
{
  sllist_push_back(variableT,key,value);

}

struct keyValuePair split_variable(const char* line) {
char *arg[5];
    int i = 0;
    int k = 0;
    strcat(line,' ');
    while(line[i] == ' '){  //leading zeroes
        i++;
    }
    while(line[i] != '\0'){
        if(line[i] != ' ' && line[i] != '='){
            arg[k] = strcat(arg[k],line[i]);
        } else { //if you encounter space , increment  the arg[] variable once for a new word
            k++; // and keep looping through that space until you reach the actual new word
            while(line[i] == ' ' || line[i] == '='){
                i++;
            }
        }
    }
    if(k < 2){
        handle_shell_log("Error in the variable assignment");
        return NULL;
    }
    // concat all subsequent values to the = and send them all as one string stored in
        // the 'data' variable
    char * data ;
    i = 1;
    while (arg[i] != NULL){
        data = strcat(data,arg[i]);
        i++;
    }
    struct keyValuePair var;
    var.key = arg[0];
    var.data = data;

    return var;
}


void print_all_variables( void )
{  int status = variableT->current == NULL ? 1 : 6;
    while (status != 1){
        fputs(variableT->current,stdout);
        status = sllist_step(variableT);
    }
    variableT->current = variableT->head;
	// you should implement this function
}