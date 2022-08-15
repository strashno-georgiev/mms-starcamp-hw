#include <stdio.h>
#include <string.h>
#include <errno.h>
int head(FILE* file) {
	int lc = 0;
	char c;
	while(lc < 10) {
		c = fgetc(file);
		if(c == '\n') lc++;
		fputc(c, stdout);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	if(argc > 1) {
		for(int i=1; i < argc; i++) {
			FILE* file = fopen(argv[i], "r");
			if(!file) {
				fprintf(stderr, "%s: %s: %s\n", argv[0], argv[i], strerror(errno));
				continue;
			}
			head(file);
			fclose(file);
		}
	}
	else {
		head(stdin);	
	}
	return 0;
}
