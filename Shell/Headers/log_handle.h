#ifndef SHELL_ERROR_HANDLE_H
#define SHELL_ERROR_HANDLE_H
/**
 * preserves the path of the logfile independant of any change in CWD , to be used by
 * other functions in the file.
 */
void prepare_logs();

/**
 * responsible for logging custom log messages to the log file and stdout.
 */
void handle_shell_log(char *message);

/**
 * responsible for logging dedicated log messages to the log file when a signal is
 * received. [SIGCHLD only]
 */
void handle_signal_shell_log(int signal);

#endif //SHELL_ERROR_HANDLE_H
