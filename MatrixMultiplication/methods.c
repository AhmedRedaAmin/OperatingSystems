#include <file_processing.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <printf.h>
#include <sys/time.h>
#include "struct_builder.h"
#include "methods.h"



void* cell_multiplyer( void* data){
struct thread_data* All = (struct thread_data* ) data;
    double** A = All->mat_A;
    double** B = All->mat_B;
    double** C = All->mat_C;
    int colA = All->colA;
    int i = All->i;
    int j = All->j;
    double sum = 0;
    for(int z = 0 ; z < colA; z++){
        sum+= A[i][z] * B[z][j];
    }
    C[i][j] = sum;
    free(data);
    //printf("The sum is %lf for MY Thread \n",sum);
    pthread_exit(NULL);

}

void* row_multiplyer( void* data){
    struct thread_data* All = (struct thread_data* ) data;
    double** A = All->mat_A;
    double** B = All->mat_B;
    double** C = All->mat_C;
    int colA = All->colA;
    int colB = All->colB;
    int i = All->i;
    int j = 0;
    while(j < colB ){
        double sum = 0;
        for(int z = 0 ; z < colA ; z++){
        sum+= A[i][z] * B[z][j];
    }
    C[i][j] = sum;
        j++;
        }
    pthread_exit(NULL);
}


void element_thread(struct thread_data* x){

    pthread_t threads[x->rowA][x->colB];
    int error;

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    for(int z = 0; z < x-> rowA; z++){
        for(int m =0 ; m < x-> colB ; m++) {
            struct thread_data* temp = malloc(sizeof(struct thread_data));
            temp->mat_A = x->mat_A;
            temp->mat_B = x->mat_B;
            temp->mat_C = x->mat_C;
            temp->i = z;
            temp->j = m;
            temp->rowA = x->rowA;
            temp->rowB = x->rowB;
            temp->colA = x->colA;
            temp->colB = x->colB;
            error = pthread_create(&threads[z][m], NULL , cell_multiplyer ,(void*)temp);
            if (error) {
                write_to_log_files("Error, thread failed to create");
                exit(-1);
            }
        }
    }

    for(int z = 0; z < x->rowA ; z++){
        for(int m =0 ; m < x->colB ; m++) {
            pthread_join(threads[z][m], NULL);
            printf("Main: completed join with thread %d %d \n",z,m);
        }
    }

    printf("Number of threads created = %d \n", x->rowA * x->colB);

    gettimeofday(&stop, NULL);
    printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);


}


void row_thread(struct thread_data* x){
    pthread_t threads[x->rowA];
    int error;

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    for(int z = 0; z < x->rowA; z++){

        struct thread_data* temp = malloc(sizeof(struct thread_data));
        temp->mat_A = x->mat_A;
        temp->mat_B = x->mat_B;
        temp->mat_C = x->mat_C;
        temp->i = z;
        temp->j = 0;
        temp->rowA = x->rowA;
        temp->rowB = x->rowB;
        temp->colA = x->colA;
        temp->colB = x->colB;
            error = pthread_create(&threads[z], NULL, row_multiplyer,(void*)temp);
            if (error) {
                write_to_log_files("Error, thread failed to create");
                exit(-1);
            }

    }

    printf("Number of threads created = %d \n",x->rowA);

    for(int z = 0; z < x->rowA ; z++){

            pthread_join(threads[z], NULL);
            printf("Main: completed join with thread %d \n",z);

    }

    gettimeofday(&stop, NULL);
    printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);


}
