#include <stdio.h>

int secondMax(const int* arr, size_t n, int* secondMax) {
	if(n == 0 || n == 1) {
		return -1;
	}
	int max = arr[0], ind=0;
	for(int i=1; i < n; i++) {
		if(arr[i] > max) {
			max = arr[i];
			ind = i;
		}
	}
	*secondMax = arr[0];
	for(int i=1; i < n; i++) {
		if(i == ind) {
			continue;
		}
		if(arr[i] > *secondMax && arr[i] < max) {
			*secondMax = arr[i];
		}
	}
	if(*secondMax == max) {
		return -2;
	}
	return 0;
}

int main() {
	int arr[] = {0, 0, 0};
	int sm;
	int res = secondMax(arr, 3, &sm);
	if(res == 0) {
		printf("%d\n", sm);
	}
	else if(res == -1) {
		printf("No second max (0 or 1 elements)\n");
	}
	else if(res == -2) {
		printf("No second max (all elements are equal)\n");
	}

}
