#ifndef MATMULTP_METHODS_H
#define MATMULTP_METHODS_H

/** This function takes a cell in the A matrix and generates its counterpart in the
 * result matrix.
 * @param i
 * @param j
 * @param matrixA
 * @param matrixB
 * @return
 */

int cell_multiplyer(int i , int j , int** matrixA , int** matrixB);

/** This function performs multithreaded matrix multiplication ont the individual
 * cell level.
 * @param matrixA
 * @param matrixB
 * @param matrixC
 */

void element_thread(int** matrixA, int** matrixB , int** matrixC);

/** This function performs multithreaded matrix multiplication on the row level.
 *
 * @param matrixA
 * @param matrixB
 * @param matrixC
 */

void row_thread(int** matrixA, int** matrixB , int** matrixC);


#endif //MATMULTP_METHODS_H
