#include <stdio.h>
#define PI 3.1415926

double pow(double base, double exp) {
	double res=1;
	for(int i=0; i < exp; i++) {
		res *= base;
	}
	return res;
}

int factorial(int num) {
	int res=1;
	while(num) {
		res *= num--;
	}
	return res;
}

double _sin(double angle, int iter) {
	double sin = 0;
	char op = 1;
	for(int i=1; i < iter * 2; i += 2) {
		if(op) {
			sin += pow(angle, i) / factorial(i);
		}
		else {
			sin -= pow(angle, i) / factorial(i);
		}
		op = !op;
	}
	return sin;
}

int main() {
	printf("%lf\n", pow(2, 1));
	printf("%d\n", factorial(1));
	printf("%lf\n", _sin(PI/6, 6));
}
