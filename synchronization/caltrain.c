#include <pthread.h>
#include "caltrain.h"



void station_init(struct station *station)
{
	pthread_mutex_init(&station->train_lock, NULL);
	pthread_cond_init(&station->train_arrived, NULL);
	pthread_cond_init(&station->passangers_on_board, NULL);

    station->waiting_train_passangers = 0;
	station->on_board_passangers = 0;
}

void station_load_train(struct station *station, int count)
{
    station->empty_seats = count;
 pthread_mutex_lock(&station->train_lock);
	while (station->empty_seats > 0 && station->waiting_train_passangers > 0 ){
        pthread_cond_broadcast(&station->train_arrived);
        pthread_cond_wait(&station->passangers_on_board, &station->train_lock);
	}
pthread_mutex_unlock(&station->train_lock);
	    station->empty_seats = 0;
}

void station_wait_for_train(struct station *station)
{
	pthread_mutex_lock(&station->train_lock);
    station->waiting_train_passangers ++;
    //passengers waiting for the next train as this train is full or there is no train yet
    while(station->on_board_passangers == station->empty_seats)
        pthread_cond_wait(&station->train_arrived, &station->train_lock);
    station->on_board_passangers ++;
    station->waiting_train_passangers --;
	pthread_mutex_unlock(&station->train_lock);}

void station_on_board(struct station *station)
{
    station->on_board_passangers --;
    station->empty_seats --;
    pthread_mutex_lock(&station->train_lock);
    //train waiting till there is no empty seat in(full train)  or all passengers seated and there is no waiting passenger.(passengers < empty seats)
    if (station->empty_seats == 0 ||(station->on_board_passangers == 0 && station->waiting_train_passangers == 0))
        pthread_cond_signal(&station->passangers_on_board);
    pthread_mutex_unlock(&station->train_lock);}






