#include <stdio.h>
#include "file_processing.h"

struct matrix* extract_matrix_from_file(char* path){






}

void write_matrix_to_file(int *Matrix[] ,char *Path){

    if(Path == NULL){
        Path = "c.txt";
    }



}

void write_to_log_files(char* message){

    FILE* input_stream = fopen(log_path,"a");
    fputs(message,input_stream);
    fputs(message,stdout);
    fclose(input_stream);
}






