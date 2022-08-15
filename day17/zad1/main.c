#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int randint(int min, int max) {
	return (rand() % (max-min)) + min;
}

char* generateString(int len) {
	char *str = calloc(len+1, sizeof(char));
	for(int i=0; i < len; i++) {
		str[i] = randint('a', 'z');
	}
	return str;
}

int main(int argc, char *argv[]) {
	int N;
	pid_t pid = getpid();
	if(argc < 2) {
		fprintf(stderr, "Usage: %s [N]\n", argv[0]);
		return -1;
	}
	N = atoi(argv[1]);
	
	for(int i=0; i < N; i++) {
		//printf("Creating process %d\n", i+1);
		pid = fork();
		if(pid < 0) {
			perror("fork");
		}
		else if(pid == 0) {
			//child
			//printf("In process %d\n", i+1);
			srand(getpid());
			char *str = generateString(10);
			printf("%s\n", str);
			free(str);
			break;
		}
	}
	for(int i=0; i < N; i++) {
		wait(NULL);
	}
	return 0;
}
