#include <pthread.h>
#include <printf.h>
#include "caltrain.h"
#include <stdio.h>


void
station_init(struct station *station) {
    station->count = 0;
    station->has_seats = 0;
    station->onboard = 0;
    pthread_mutex_init(&Train_count, NULL);
    pthread_cond_init(&Train_arrived, NULL);
    pthread_cond_init(&Train_ready, NULL);
}

void
station_load_train(struct station *station, int count) {
    if (count == 0) return;
    pthread_mutex_lock(&Train_count);
    if (station->count == 0) {
        pthread_mutex_unlock(&Train_count);
        return;
    }
    station->onboard = count;
    station->has_seats = count;
    pthread_cond_broadcast(&Train_arrived);
    while (station->onboard != 0 && station->count != 0) {
        printf("this should happen only one time\n");

        pthread_cond_wait(&Train_ready, &Train_count);
    }
    station->onboard = 0;
    station->has_seats = 0;
    pthread_mutex_unlock(&Train_count);
    // FILL ME IN
}

void
station_wait_for_train(struct station *station) {
    pthread_mutex_lock(&Train_count);
    station->count ++ ;
    while(station->has_seats == 0) {
        pthread_cond_wait(&Train_arrived, &Train_count);
    }
    station->to_be_seated ++;
    station->count--;
    station->has_seats --;
    pthread_cond_broadcast(&Train_arrived);
    pthread_mutex_unlock(&Train_count);

}

void
station_on_board(struct station *station) {
    pthread_mutex_lock(&Train_count);
    station->to_be_seated--;
    station->onboard--;
    if ((station->onboard <= 0 || station->count == 0)&&(station->to_be_seated == 0)) {
        printf("free onboard seats are %d\n",station->onboard);
        printf("Still in station are %d\n",station->count);
        pthread_cond_broadcast(&Train_ready);
    }

    pthread_mutex_unlock(&Train_count);
}
