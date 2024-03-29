#ifndef VARIABLES_H_   /* Include guard */
#define VARIABLES_H_

/**
 *  Builds the singly linked list implemented in sllist.c
 *  and loads primary environment variables , HOME , PATH  , into it .
 */
void setup_variables_table();
/**
	- This function should be responsible for getting the value of a variable
	- To execute commands, You must always search for the executable files 
	  in the value returned by lookup_variable("PATH");
	- Your code must be dynamic and can handle any number of variables, However,
	  performance is not an issue since in practice we expect low number of variables,
	  as a tip: simple array lookup would be fine
*/
char* lookup_variable( const char* key );

/**
	- This function should be responsible for setting the value of a variable
*/
void set_variable( char* key , char* value );

/**
	[OPTIONAL] Doesn't affect the code logic
	- This is a helper function to print all your variables
	- Might help much in the debugging or testing
*/
void print_all_variables( void );
/**
 *  Destroys the previously built variables table , freeing its place in memory.
 */
void free_variables_table();

#endif // VARIABLES_H_