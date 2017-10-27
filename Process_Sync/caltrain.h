#include <pthread.h>



static pthread_mutex_t Train_count;
static pthread_cond_t Train_arrived,Train_ready;


struct station {
    volatile int count;
    volatile int onboard;
    volatile int has_seats;
    volatile int to_be_seated;
    // FILL ME IN
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);