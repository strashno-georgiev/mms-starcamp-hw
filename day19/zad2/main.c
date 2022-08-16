#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

int compar(const void* num1, const void* num2) {
	return (*(int*)num1) - (*(int*)num2);
}

void* procedure(void *data) {
	FILE* file;
	int size = 10, res, curr_size = 0, read_am=5;
	int32_t *nums;
	file = fopen((char*)data, "rb");
	if(!file) {
		fprintf(stderr, "%s: %s\n", (char*)data, strerror(errno));
		pthread_exit(NULL);
	}
	nums = calloc(size, sizeof(int32_t));
	while(1) {
		if(curr_size > size - read_am) {
			size += 10;
			nums = realloc(nums, size);
		}
		res = fread(nums+curr_size, sizeof(int32_t), read_am, file);
		curr_size += res;
		if(res < read_am) {
			if(feof(file)) {
				break;
			}
			else {
				perror("fread");
				pthread_exit(NULL);
			}
		}
	}
	/*printf("%s: \n", (char*)data);
	for(int i=0; i < curr_size; i++) {
		printf("%d\n", nums[i]);
	}*/
	qsort(nums, curr_size, sizeof(int32_t), compar);
	fclose(file);
	
	file = fopen((char*)data, "wb");
	fwrite(nums, sizeof(int32_t), curr_size, file);
	free(nums);
	fclose(file);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		fprintf(stderr, "Usage: %s <file> [...]\n", argv[0]);
		return -1;
	}
	pthread_t *threads = calloc(argc-1, sizeof(pthread_t));
	
	for(int i=0; i < argc-1; i++) {
		pthread_create(threads+i, NULL, procedure, argv[i+1]);
	}
	
	pthread_exit(NULL);
}	
