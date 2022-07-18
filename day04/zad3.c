//numsystem converter
#include <stdio.h>
#include <stdlib.h>

int main() {
	char number[128];
	int outbase, inbase;
	printf("Enter number: ");
	scanf("%s", &number);
	printf("Enter input number system base:");
	scanf("%d", &inbase);
	
	printf("Enter output number system base:");
	scanf("%d", &outbase);
	
	int num = strtol(number, NULL, inbase);
	//printf("%d\n", num);
	char output[128];
	int i = 0;
	while(num > 0) {
		int rem = num % outbase;
		output[i] = rem < 10 ? rem + '0' : rem + 'a' - 10; 
		i++;
		num /= outbase;
	}
	output[i] = '\0';
	for(i -= 1 ; i >= 0 ; i--) {
		printf("%c", output[i]);
	}
	printf("\n");
	
	
}
