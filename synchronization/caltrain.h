#include <pthread.h>

struct station {

	pthread_mutex_t train_lock;
    pthread_cond_t train_arrived;
	pthread_cond_t passangers_on_board;

    int empty_seats;
	int waiting_train_passangers;
	int on_board_passangers;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);
