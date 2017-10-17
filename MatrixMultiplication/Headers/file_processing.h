#ifndef MATMULTP_FILE_PROCESSING_H
#define MATMULTP_FILE_PROCESSING_H


const char* log_path = "./Resources/logs.txt";


/** structure in which the fetched matrices can be stored.**/

struct matrix{
    int length;
    int widtth;
    char** values;
};

/** This function extracts all of the matrix from the file , storing it in
 * a struct of type matrix , ready for processing .
 * @param path
 * @return
 */

struct matrix* extract_matrix_from_file(char* path);

/** This function writes the resultant matrix into a file .
 * @param Matrix
 * @param Path
 */

void write_matrix_to_file(int *Matrix[] ,char *Path);

/** This function is responsible for logging .
 * @param message
 */

void write_to_log_files(char* message);











#endif //MATMULTP_FILE_PROCESSING_H
