#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if(argc < 3) {
		fprintf(stderr, "Usage: %s <file> <num1> [...]\n", argv[0]);
	}
	FILE* file = fopen(argv[1], "w");
	for(int i=2; i < argc; i++) {
		int num = atoi(argv[i]);
		fwrite(&num, sizeof(num), 1, file);
		printf("%d\n", num);
	} 
	
	fclose(file);
	return 0;
}
