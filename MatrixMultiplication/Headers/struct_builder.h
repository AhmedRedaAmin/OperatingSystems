//
// Created by ahmed on 10/21/17.
//

#ifndef MATMULTP_STRUCT_BUILDER_H
#define MATMULTP_STRUCT_BUILDER_H

/** Struct for the thread Data.**/
struct thread_data{
    double** mat_A;
    double** mat_B;
    double** mat_C;
    int rowA,rowB,colA,colB;
    int i,j;
};

struct thread_data* build_struct( double** matA, double** matB , double**matC,int rowA ,int colA,int rowB,
                                 int colB);

#endif //MATMULTP_STRUCT_BUILDER_H
