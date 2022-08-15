#include <stdio.h>
#include <string.h>
#include <errno.h>


int main(int argc, char* argv[]) {
	if(argc == 1) {
		fprintf(stderr, "%s: missing file operand\n", argv[0]);
		return -1;
	}
	else if(argc == 2) {
		fprintf(stderr, "%s: missing destination file operand after '%s'\n", argv[0], argv[1]);
		return -1;
	}
	else {
		FILE* src = fopen(argv[1], "r");
		if(!src) {
			fprintf(stderr, "%s: %s: %s\n", argv[0], argv[1], strerror(errno));
		}
		FILE* dest = fopen(argv[2], "w");
		if(!dest) {
			fprintf(stderr, "%s: %s: %s\n", argv[0], argv[2], strerror(errno));
		}		
		char c;
		while((c = fgetc(src)) != EOF) {
			fputc(c, dest);
		}
		remove(argv[1]);
		
		return 0;
	}
	return -1;
}
