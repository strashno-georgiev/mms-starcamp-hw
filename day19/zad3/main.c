#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/wait.h>

void* procedure(void *data) {
	printf("P%u, Thread %lu: %s\n", getpid(), pthread_self(), (char*)data);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	if(argc < 4) {
		fprintf(stderr, "Usage: %s <P> <T> <message>\n", argv[0]);
		return -1;
	}
	unsigned int P, T;
	int res;
	pid_t pid = getpid();
	pthread_t *threads;
	P = atoi(argv[1]);
	T = atoi(argv[2]);
	for(int i=0; i < P ; i++) {
		pid = fork();
		if(pid == 0) {
			threads = calloc(T, sizeof(pthread_t));
			for(int j=0; j < T; j++) {
				pthread_create(threads+j, NULL, procedure, argv[3]);
			}
			
			free(threads);
			
			pthread_exit(0);
		}
	}
	
	while((res = wait(NULL)) > 0);
	
	return 0;	
}
