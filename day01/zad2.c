#include <stdio.h>
#include <math.h>
#define PI 3.1416
double straight_cyllinder(int R, int H) {
	return M_PI * pow(R, 2) * H;
}
double horizontal_cyllinder(int R, int L, int H) {
	double angle = acos(((double)(R-H))/R);
	printf("%lf\n", angle);
	return L * (angle * pow(R, 2) - (R - H) * sqrt(2 * R * H - pow(H, 2)));
} 
int main() {
	int R, L, H;
	scanf("%d %d %d", &R, &L, &H);
	printf("%lf\n", straight_cyllinder(R, H));
	printf("%lf\n", horizontal_cyllinder(R, L, H));
	return 0;
}
