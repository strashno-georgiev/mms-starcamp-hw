#include <stdio.h>
#define BAB_RUNS 100

double babylonian_sqrt(int num) {
	double appr = num / 2.0;
	for(int i=0; i < BAB_RUNS; i++) {
		appr = (appr + num / appr) / 2;
	}
	return appr;
}

int main() {
	printf("%.5lf\n", babylonian_sqrt(2));
	printf("%.5lf\n", babylonian_sqrt(25));
}
