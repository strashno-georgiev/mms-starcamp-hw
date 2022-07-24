#include <stdio.h>

int digitSum(int num) {
	int sum = 0;
	while(num > 0) {
		sum += num % 10;
		num /= 10;
	}
	return sum;
}

int sumArrayDigits(const int* arr, size_t n) {
	int sum = 0;
	for(int i=0; i < n; i++) {
		sum += digitSum(arr[i]);
	}
	return sum;
}

int main() {
	int arr[] = {13, 45};
	printf("%d\n", sumArrayDigits(arr, 2));
	return 0;
}
