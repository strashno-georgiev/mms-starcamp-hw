#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int cat(FILE* file) {
	char c;
	while((c = fgetc(file)) != EOF) {
		fputc(c, stdout);
	}
	return 0;
}

int cat_stdin() {
	int i=0;
	size_t size = 20;
	char *c = calloc(size, sizeof(char));
	
	while((c[i] = fgetc(stdin)) != EOF) {
		i++;
		if(i == size) {
			size *= 2;
			c = realloc(c, size);
		}
	}
	
	for(int j=0; j < i; j++) {
		fputc(c[j], stdout);
	}
	free(c);
	return 0;
}


int main(int argc, char* argv[]) {
	if(argc < 2) {
		cat_stdin();
	}
	else {
		int file_count = argc-1;
		FILE* file;
		for(int i=1; i < file_count+1; i++) {
			file = fopen(argv[i], "r");
			if(!file) {
				fprintf(stderr, "%s: %s: %s\n", argv[0], argv[i], strerror(errno));
				return -1;
			}
			cat(file);
			fclose(file);
		}
	}
	return 0;
}
