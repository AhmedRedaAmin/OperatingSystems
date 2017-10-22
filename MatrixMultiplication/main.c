#include <stdlib.h>
#include <file_processing.h>
#include <memory.h>
#include <methods.h>
#include <struct_builder.h>

int check_for_file(char* path);
void Matrix_computing(char* arg,struct thread_data* data);



void main( int argc ,char *argv[]){

    if (argc == 4){ //If arguments are provided.
        printf("starting read from file \n");
        if(check_for_file(argv[1])&& check_for_file(argv[2])) { //We check to see if input
            int rowA,rowB,colA,colB;                            //args are valid file paths.
            FILE *file = fopen(argv[1], "r");
            fscanf(file,"row=%d col=%d",&rowA,&colA);
            double** matA = malloc(sizeof(double*)*rowA);
            for(int z = 0 ;z < rowA; z++ ){
                matA[z] = malloc(sizeof(double)*colA);
            }
            extract_matrix_from_file(file,matA,rowA,colA);
            fclose(file);
            file = fopen(argv[2], "r");
            fscanf(file,"row=%d col=%d",&rowB,&colB);
            double** matB = malloc(sizeof(double*)*rowB);
            for(int z = 0 ;z < rowB; z++ ){
                matB[z] = malloc(sizeof(double)*colB);
            }
            extract_matrix_from_file(file,matB,rowB,colB);
            fclose(file);
            double** matC = malloc(sizeof(double*)*rowA);
            for(int z = 0 ;z < rowA; z++ ){
                matC[z] = malloc(sizeof(double)*colB);
            }
            struct thread_data* context = build_struct(matA,matB,matC,rowA,colA,rowB,colB);

            Matrix_computing(argv[3],context);
            free(context);
        } else {
            write_to_log_files("invalid file names , closing program \n");
            exit(0);
        }
    } else { //If arguments aren`t provided.
        printf("Wrong number of inputs, starting from default files \n");
        int rowA,rowB,colA,colB;
        FILE *file = fopen("./test/a.txt", "r");
        fscanf(file,"row=%d col=%d",&rowA,&colA);
        double** matA = malloc(sizeof(double*)*rowA);
        for(int z = 0 ;z < rowA; z++ ){
            matA[z] = malloc(sizeof(double)*colA);
        }
        extract_matrix_from_file(file,matA,rowA,colA);
        fclose(file);
        file = fopen("./test/b.txt", "r");
        fscanf(file,"row=%d col=%d",&rowB,&colB);
        double** matB = malloc(sizeof(double*)*rowB);
        for(int z = 0 ;z < rowB; z++ ){
            matB[z] = malloc(sizeof(double)*colB);
        }
        extract_matrix_from_file(file,matB,rowB,colB);
        fclose(file);
        double** matC = malloc(sizeof(double*)*rowA);
        for(int z = 0 ;z < rowA; z++ ){
            matC[z] = malloc(sizeof(double)*colB);
        }
        struct thread_data* context = build_struct(matA,matB,matC,rowA,colA,rowB,colB);

        Matrix_computing("./test/c.txt",context);
        free(context);
    }

}


//Checks validity of file paths.
int check_for_file(char* path){
    FILE* f = fopen(path,"r");
    if(f == NULL){
        return 0;
    }
    fclose(f);
    return 1;
}
//Performs the actual computing part + implements part of the output logic.
void Matrix_computing(char* arg,struct thread_data * data){

    char temp[strlen(arg)+15];
    memset(temp,0,strlen(arg)+15);
    strcat(temp,arg);
    strcat(temp,"_cell_by_cell");
    element_thread(data);
    write_matrix_to_file(temp,data->mat_C,data->rowA,data->colB);

    memset(temp,0,strlen(temp));
    strcat(temp,arg);
    strcat(temp,"_row_by_row");
    row_thread(data);
    write_matrix_to_file(temp,data->mat_C,data->rowA,data->colB);
    return;
}