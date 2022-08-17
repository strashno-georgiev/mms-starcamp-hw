#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>
#include <signal.h>
#include "list.h"

#define DELIVERY_SLEEP 3
#define BUYER_SLEEP 2

typedef struct list_t list_t;


int64_t randint(int64_t min, int64_t max) {
	return (rand() % (max-min)) + min;
}

double randreal(double min, double max) {
	return ((double)rand() / (double)RAND_MAX) * (max - min) + min;
}

product_t randProduct() {
	product_t new;
	new.barcode = randint(0, INT_MAX);
	new.description = randint(vegetable, herb+1);
	new.price = randreal(0.5, 150.0);
	return new;
}

void printProduct(product_t p) {
	static char *types[] = {"vegetable", "appliance", "clothing", "shoes", "bread", "fruit", "accessory", "meat", "herb"};
	printf("\n\t%u\n\t%s\n\t%lf\n", p.barcode, types[p.description], p.price);
}

void exit_handler(int signal);

void* buyer(void *data);

void* delivery_man(void *data);

int CAPACITY = 10;
int SIZE = 0, D, B;
list_t STORAGE;
pthread_mutex_t MUTEX;
pthread_t *delivery;
pthread_t *buyers;
char STOP_THREADS = 0;

int main(int argc, char *argv[]) {
	D = 5;
	B = 6;
	delivery = calloc(D, sizeof(pthread_t));
	buyers = calloc(B, sizeof(pthread_t));
	pthread_mutex_init(&MUTEX, NULL);
	struct sigaction act;
	act.sa_handler = exit_handler;
	sigaction(SIGINT, &act, NULL);
	
	for(int i=0; i < D; i++) {
		pthread_create(delivery+i, NULL, delivery_man, NULL);
	}
	for(int i=0; i < B; i++) {
		pthread_create(buyers+i, NULL, buyer, NULL);
	}
	
	pthread_join(delivery[0], NULL);
	
	free(buyers);
	free(delivery);	
	destroy_list(&STORAGE);
	pthread_mutex_destroy(&MUTEX);
	
	
	return 0;
}

void exit_handler(int signal) {
	STOP_THREADS = 1;
	
	for(int i=0; i < D; i++) {
		pthread_join(delivery[i], NULL);
	}
	for(int j=0; j < B; j++) {
		pthread_join(buyers[j], NULL);
	}
	
	free(buyers);
	free(delivery);	
	destroy_list(&STORAGE);
	pthread_mutex_destroy(&MUTEX);
}


void* buyer(void *data) {
	int index; 
	product_t product;
	while(!STOP_THREADS) {
		pthread_mutex_lock(&MUTEX);
		index = randint(0, SIZE);
		product = detach(&STORAGE, list_index(&STORAGE, index));
		SIZE--;
		printf("Removed product from storage:");
		printProduct(product);
		pthread_mutex_unlock(&MUTEX);
		sleep(BUYER_SLEEP);
	}
	pthread_exit(NULL);
}	

void* delivery_man(void *data) {
	product_t product;
	while(!STOP_THREADS) {
		product = randProduct();
		pthread_mutex_lock(&MUTEX);
		push_back(&STORAGE, product);
		SIZE++;

		printf("Added new product to storage:");
		printProduct(product);
		pthread_mutex_unlock(&MUTEX);
		sleep(DELIVERY_SLEEP);
	}
	pthread_exit(NULL);
}
