#include <stdio.h>
#include <math.h>
#include <string.h>
int rectangle(double a, double b, double* S, double* P) {
	if(a <= 0 || b <= 0) {
		return -1;
	}
	*P = (a+b) * 2;
	*S = a * b;
	return 0;
}

int main() {
	char line[128];
	double a, b, c, S, P;
	char ch;
	while((ch = fgetc(stdin)) != EOF) {
		ungetc(ch, stdin);
		fgets(line, 128, stdin);
		int res = sscanf(line, "%lf %lf", &a, &b);
		if(res == EOF) {
			break;
		}
		else if(res < 3) {
			printf("Invalid triangle sides!\n");
			continue;
		}
		if(rectangle(a, b, &S, &P) == -1) {
			printf("Invalid triangle sides!\n");
			continue;
		}
		printf("S = %.2lf\n", S);
		printf("P = %.2lf\n", P);		
	}
	return 0;
}
