#include <file_processing.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <printf.h>
#include <sys/time.h>
#include "struct_builder.h"
#include "methods.h"

void * print_hello_world(void* tid)
{
//print identification of thread and exit
    printf("Thread : Hello World \n");
    pthread_exit(NULL);
}




void* cell_multiplyer( void* data){
struct thread_data* All = (struct thread_data* ) data;
    printf("hi there \n");
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
            x->i =z;
            x->j =m;
            error = pthread_create(&threads[z][m], NULL , cell_multiplyer ,(void*)x);
            if (error) {
                write_to_log_files("Error, thread failed to create");
                exit(-1);
            }
        }
    }
    printf("Number of threads created = %d \n", x->rowA * x->colB);

    for(int z = 0; z < x->rowA ; z++){
        for(int m =0 ; m < x->colB ; m++) {
        pthread_join(threads[z][m], NULL);
        printf("Main: completed join with thread %d %d \n",z,m);
        }
    }


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

            x->i =z;
            x->j =0;
            error = pthread_create(&threads[z], NULL, row_multiplyer,(void*)x);
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
