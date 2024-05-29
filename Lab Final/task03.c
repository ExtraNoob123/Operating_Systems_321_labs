#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define num_checkin_counters 5
#define num_immigration_counters 1
#define train_capacity 4
#define num_passengers 6

pthread_mutex_t checkin_mutex = pthread_mutex_initializer;
pthread_mutex_t immigration_mutex = pthread_mutex_initializer;
pthread_mute_t train_mutex = pthread_mutex_initializer;
sem_t checkin_sem;
sem_t immigration_sem;

void* passenger(void* id_ptr) {
	int id = *((int*)id_ptr);
	
	printf("Passenger %d: Arrived at check-in counter.\n", id);
	pthread mutex_lock(&checkin_mutex);
	sem_wait(&checkin_sem);
	printf("Passenger %d: Checking in...\n", id);
	sleep(1);
	sem_post(&checkin_sem);
	pthread_mutex_unlock(&checkin_mutex);
	printf("Passenger %d: Checked in.\n", id);
	
	printf("Passenger %d: Proceeding to immigration counter.\n", id);
	pthread_mutex_lock(&immigration_mutex);
	sem_wait(&immigration_sem);
	printf("Passenger %d: Passing through immigration...\n", id);
	sleep(2);
	sem_post(&immigration_sem);
	pthread_mutex_unlock(&immigration_mutex);
	printf("Passenger %d: Cleared immigration.\n", id);
	
	printf("Passenger %d: Boarding the train. \n", id);
	pthread_mutex_lock(&train_mutex);
	printf("Passenger %d: Train departed with passengers.\n", id);
	sleep(3);
	pthread_mutex_unlock(&train_mutex);
	printf("Passenger %d: Arrived at the plane.\n", id);
	
	return NULL;
}

int main() {
	pthread_t threads[num_passengers];
	sem_init(&checkin_sem, 0, num_checkin_counters);
	sem_init(&immigration_sem, 0, num_immigration_counters);
	
	int ids[num_passengers];
	for(int i = 0; i < num_passengers; i++) {
		ids[i] = i +1;
		pthread_create(&threads[i], NULL, passenger, &ids[i]);
	}
	
	for (int i = 0; i < num_passengers; i++) {
		pthread_join(threads[i], NULL);
	}
	
	sem_destroy(&checkin_sem);
	sem_destroy(&immigration_sem);
	
	return 0
	

















	
	
	
	
	
	
	
	
	
	
