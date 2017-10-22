#ifndef MATMULTP_METHODS_H
#define MATMULTP_METHODS_H

#include "struct_builder.h"

/** This function takes a cell in the A matrix and generates its counterpart in the result matrix.
 *
 * @param data
 * @return
 */

void* cell_multiplyer(void* data);

/** This function takes a row in the A matrix and generates its counterpart in the result matrix.
 *
 * @param data
 * @return
 */
void* row_multiplyer( void* data);

/** This function performs multithreaded matrix multiplication ont the individual cell level.
 *
 * @param x
 */

void element_thread(struct thread_data* x);

/** This function performs multithreaded matrix multiplication on the row level.
 *
 * @param y
 */

void row_thread(struct thread_data* y);


#endif //MATMULTP_METHODS_H
