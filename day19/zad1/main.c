#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int randint(int min, int max) {
	return (rand() % (max-min)) + min;
}

char* generateString(int len) {
	char *str = calloc(len+1, sizeof(char));
	for(int i=0; i < len; i++) {
		str[i] = randint('a', 'z'+1);
	}
	return str;
}

void* procedure(void *data) {
	printf("%s\n", generateString(10));
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		fprintf(stderr, "Usage: %s <N>\n", argv[0]);
		return -1;
	}
	int N = atoi(argv[1]);
	pthread_t *threads = calloc(N, sizeof(pthread_t));
	for(int i=0; i < N; i++) {
		pthread_create(threads+i, NULL, procedure, NULL);
	}
	free(threads);
	pthread_exit(0);
}
