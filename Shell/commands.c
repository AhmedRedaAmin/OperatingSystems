#include <unistd.h>
#include <variables.h>
#include <memory.h>
#include "commands.h"


void cd( const char* path )
{
	char* args[] = {"cd", path ,(char*)0};
    execv(strcat(lookup_variable("PATH"),"/cd"),args);
}  


void echo( const char* message )
{
    char* args[] = {"echo", message ,(char*)0};
    execv(strcat(lookup_variable("PATH"),"/echo"),args);
	// you should implement this function
}