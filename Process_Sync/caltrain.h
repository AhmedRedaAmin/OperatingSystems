#include <pthread.h>


/** Train_count is the mutex lock we are using for this struct ,
	Train_arrived is the condition variable for train arrival,
	Train_arrived is the condition variable when the train is ready to leave the station.
**/
static pthread_mutex_t Train_count;
static pthread_cond_t Train_arrived,Train_ready;

/** count is the number of people as counted by the station master,
	onboard is the number of people as counted by the train conductor,
	has_seats is the number of available seats on the train,
	to_be_seated is the number of people moving to their seats onboard the train.
	All variables are volatile to ensure thread safety.
**/
struct station {
    volatile int count;
    volatile int onboard;
    volatile int has_seats;
    volatile int to_be_seated;
    // FILL ME IN
};

/**
	initiates the station struct.
**/
void station_init(struct station *station);
/**
	Indicates the arrival of a train thread , it activates the train arrived condition
	variable and waits for the train ready condition variable , it returns when the
	train is ready to leave.
**/
void station_load_train(struct station *station, int count);

/**
	The function implemented by the passenger threads, it keeps track of their number in
	the station , and the number of people moving to board the train , returns when a
	passenger thread has started moving to board the train.
**/
void station_wait_for_train(struct station *station);

/**
	This function is called for every passenger moving towards the train in order to document
	how many people are moving and whether they are seated in the train or not , a passenger is
	in the train only if he is seated , and by that I mean if he executes and returns this function,
	This function controls when the train is ready to leave , by signalling the train ready condition
	variable. [note: this function isn`t implemented by the threads but rather in the main at the end of
	a train call, the threads that performed wait for train and returned call this function and
	are counted in sequence and then their count considered the valid number of seated passengers by the main]
**/
void station_on_board(struct station *station);