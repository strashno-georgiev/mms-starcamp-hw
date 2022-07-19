#include <stdio.h>
int main() {
	double op1, op2, res;
	char operator, eof = 0;
	while(1) {
		int r = scanf("%lf %c %lf", &op1, &operator, &op2);
		if(r == EOF) {
			break;
		}
		if(r < 3) {
			fprintf(stderr, "Invalid expression\n");
		}
		switch(operator) {
			case '+':
				res = op1 + op2;
				break;
			case '-':
				res = op1 - op2;
				break;
			case '*':
				res = op1 * op2;
				break;
			case '/':
				res = op1 / op2;
				break;
			default:
				fprintf(stderr, "Invalid expression\n");
		}
		printf("%.2lf\n", res);
	}
	return 0;
}	
