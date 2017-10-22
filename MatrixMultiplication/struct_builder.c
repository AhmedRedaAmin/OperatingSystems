#include <stdlib.h>
#include "struct_builder.h"


struct thread_data* build_struct( double** matA, double** matB , double**matC,int rowA ,int colA,int rowB,
                                 int colB){

    struct thread_data* context = malloc(sizeof(struct thread_data));
    context->mat_A = matA;
    context->mat_B = matB;
    context->mat_C = matC;
    context->colA = colA;
    context->rowA = rowA;
    context->colB = colB;
    context->rowB = rowB;
    return context;
}