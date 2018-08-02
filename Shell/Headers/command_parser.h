#ifndef COMMAND_PARSER_H   /* Include guard */
#define COMMAND_PARSER_H

static const int MAX_LENGTH = 512; //maximum input length
enum SHELL_MODE {EXECUTE , COMMAND , VARIABLE }; //operation modes



/** this function splits the command by space into tokens
 *
 * @param command
 * @return
 */
char ** split_command(char* command );
/** this function checks for a trailing ampersand
 *
 * @param arguments
 * @return
 */
int check_background(char ** arguments);
/** this function checks for any variables that need to be unpacked
 *
 * @param arguments
 * @return
 */
char** variable_processing(char** arguments);
/** this function identify the operation modes mentioned above
 *
 * @param Arguments
 * @return
 */
enum SHELL_MODE identify_command(char** Arguments);
/** this function executes the commands
 *
 * @param Arguments
 * @param status
 */
void exec_command(char ** Arguments , int status);

/** this function counts tokens
 * and initialize an array of pointers of known size;
 */
void tokenize(char * str , char * delimeter ,char ** arguments);

#endif // COMMAND_PARSER_H