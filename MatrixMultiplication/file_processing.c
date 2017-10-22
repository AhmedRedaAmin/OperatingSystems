#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "file_processing.h"



double **extract_matrix_from_file( FILE* file, double **matrix, int rows, int cols) {
    if (file == NULL) {
        return matrix;
    }

    for (int i = 0; i < rows; i++) {
        for(int j = 0 ;j < cols ; j++){
            fscanf(file,"%lf",&matrix[i][j]);
        }
    }


    return matrix;
}

void write_matrix_to_file(char* path, double **matrix, int rows, int cols) {
    FILE* file = fopen(path,"a");
    if (file == NULL) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%lf\t", matrix[i][j]);
            printf("%lf\t", matrix[i][j]);
        }
        fprintf(file, "\n");
        printf("\n");
    }
    fclose(file);
}

void write_to_log_files(char *message) {

    FILE *input_stream = fopen(log_path, "a");
    fputs(message, input_stream);
    fputs(message, stdout);
    fclose(input_stream);
}






