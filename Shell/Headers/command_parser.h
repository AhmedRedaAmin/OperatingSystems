#ifndef COMMAND_PARSER_H   /* Include guard */
#define COMMAND_PARSER_H

static const int MAN_LENGTH = 512; //mandatory length
static const int EXECUTE = 1;
static const int COMMAND = 2;
static const int VARIABLE = 3;


/*
 * - This function splits a variable line into a key value pair
*/


/* 
	- This function should be responsible for importing all details of the command 
	- Should specify the type of the command "comment, cd, echo, expression - X=5 -, else"
	- Should specify the arguments of the command
	- Should specify if the command is background or foreground
	- Should consider all parsing special cases, example: many spaces in  "ls     -a"

	- You're left free to decide how to return your imported details of this command

	- Best practice is to use helper function for each collection of logical instructions,
	  example: function for splitting the command by space into array of strings, ..etc
*/
char ** split_command(char* command );

int check_background(char ** arguments);

char** variable_processing(char** arguments);

int identify_command(char** Arguments);

void exec_command(char ** Arguments , int status);

// count tokens and initialize an array of pointers of known size;
void tokenize(char * str , char * delimeter ,char ** arguments);

#endif // COMMAND_PARSER_H