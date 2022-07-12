#include <stdio.h>
#include <math.h>

double BMI(int mass, double height) {
	return mass / (pow(height, 2));
}

double BMI_new(int mass, double height) {
	return 1.3 * mass / pow(height, 2.5);
}

int main() {
	int mass;
	double height;
	scanf("%d %lf", &mass, &height);
	printf("BMI 1 - %lf\n", BMI(mass, height));
	printf("BMI new - %lf\n", BMI_new(mass, height));
	return 0;
}
