#ifndef MATMULTP_FILE_PROCESSING_H
#define MATMULTP_FILE_PROCESSING_H

#include <stdio.h>

static const char* log_path = "./Resources/logs.txt";




/** This function extracts all of the matrix from the file  , ready for processing.
 *
 * @param file
 * @param matrix
 * @param rows
 * @param cols
 * @return
 */

double** extract_matrix_from_file(FILE* file, double **matrix, int rows, int cols);

/** This function writes the resultant matrix into a file .
 *
 * @param path
 * @param Matrix
 * @param x
 * @param y
 */

void write_matrix_to_file(char* path,double **Matrix , int x , int y);

/** This function is responsible for logging .
 *
 * @param message
 */

void write_to_log_files(char* message);




#endif //MATMULTP_FILE_PROCESSING_H
