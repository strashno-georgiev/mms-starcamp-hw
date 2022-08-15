#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PIPE_READ 0
#define PIPE_WRITE 1
int main(int argc, char *argv[]) {
	int sum = 0, sum_recv = 0, r;
	int pipefd[2];
	if((pipe(pipefd))) {
		perror("pipe");
	}
	pid_t pid = fork();
	if(pid == 0) {
		for(int i=argc/2; i < argc; i++) {
			sum += atoi(argv[i]);
		}
		write(pipefd[PIPE_WRITE], &sum, sizeof(sum));
		return 0;
	}
	for(int i=1; i < argc / 2; i++) {
		sum += atoi(argv[i]);
	}
	r = read(pipefd[PIPE_READ], &sum_recv, sizeof(sum));
	if(r < 0) {
		perror("read");
	}
	printf("Sum total is %d\n", sum + sum_recv);
	return 0;
	
}
