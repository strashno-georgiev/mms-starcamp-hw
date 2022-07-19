#include <stdio.h>
#include <math.h>
#include <string.h>
int triangle(double a, double b, double c, double* S, double* P) {
	if((a + b <= c) || (a + c <= b) || (c + b <= a)) {
		return -1;
	}
	*P = a+b+c;
	double p = *P / 2;
	*S = sqrt(p * (p-a) * (p-b) * (p-c));
	return 0;
}

int main() {
	char line[128];
	double a, b, c, S, P;
	char ch;
	while((ch = fgetc(stdin)) != EOF) {
		ungetc(ch, stdin);
		fgets(line, 128, stdin);
		int res = sscanf(line, "%lf %lf %lf", &a, &b, &c);
		if(res == EOF) {
			break;
		}
		else if(res < 3) {
			printf("Invalid triangle sides!\n");
			continue;
		}
		if(triangle(a, b, c, &S, &P) == -1) {
			printf("Invalid triangle sides!\n");
			continue;
		}
		printf("S = %.2lf\n", S);
		printf("P = %.2lf\n", P);		
	}
	return 0;
}
