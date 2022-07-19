#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int quadEq(double a, double b, double c, double* x1, double* x2) {
	double D = pow(b, 2) - 4 * a * c;
	if(D < 0) {
		return -1;
	}
	*x1 = (-b + sqrt(D)) / (2*a);
	*x2 = (-b - sqrt(D)) / (2*a);
	return 0;
}

int main(int argc, char* argv[]) {
	double x1, x2;
	if(argc < 4) {
		fprintf(stderr, "Not enough arguments");
	}
	quadEq(atof(argv[1]), atof(argv[2]), atof(argv[3]), &x1, &x2);
	printf("x1 = %lf\nx2 = %lf\n", x1, x2);
	
	return 0;
}
