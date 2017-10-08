#include <sllist.h>
#include <stdio.h>
#include <log_handle.h>
#include <stdlib.h>
#include <command_parser.h>
#include <memory.h>
#include "variables.h"
#include "file_processing.h"

struct sllist* variableT;

void setup_variables_table(){
    variableT = sllist_create();
    set_variable("PATH",getenv("PATH"));
    set_variable("HOME",getenv("HOME"));

}
char* lookup_variable( const char* key )
{   variableT->current = variableT->head;
    int status = variableT->current == NULL ?  1 : 6 ;
    char* value;
    while (status != 1){
        int i = 0;
        status = sllist_step(variableT);
        int compare = strcmp(key,variableT->current->key);
        if (compare == 0){
            value = variableT->current->data;
        }
    }
    variableT->current = variableT->head;
    if (value == NULL){
        value = getenv(key);
    }
    // means that the variable hasn`t been found if value == NULL
    return value;

}

void set_variable( char* key , char* value )
{
  sllist_push_back(variableT,key,value);

}

void print_all_variables( void )
{  int status = variableT->current == NULL ? 1 : 6;
    while (status != 1){
        char* key = variableT->current->key;
        char* value = variableT->current->data;
        fputs(key,stdout);
        fputs(value,stdout);
        status = sllist_step(variableT);
    }
    variableT->current = variableT->head;
	// you should implement this function
}

void free_variables_table(){
    sllist_destroy(variableT);

}