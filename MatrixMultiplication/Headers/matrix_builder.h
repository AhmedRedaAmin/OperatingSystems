#ifndef MATMULTP_MATRIX_BUILDER_H
#define MATMULTP_MATRIX_BUILDER_H


#include "file_processing.h"

/** This function builds a numerical 2D array from a matrix struct .
 *
 * @param len
 * @param width
 * @param Matrix
 * @param MatrixS
 */

void build_matrix(int len , int width , int Matrix[len][width] , struct matrix MatrixS);

/** This function builds a row in a 2D array by parsing a character array .
 *
 * @param line
 * @return
 */

int* line_parser(char* line);

#endif //MATMULTP_MATRIX_BUILDER_H
