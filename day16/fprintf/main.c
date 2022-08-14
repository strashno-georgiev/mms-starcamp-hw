#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

//to 6 digits after the point
char* rtoa(double num) {
	int stack_size = 20;
	int stack_top = 0;
	unsigned int wholep = num;
	int fpoint = 0, counter, i;
	char* str = malloc((stack_size+2) * sizeof(char));
	
	//printf("Converting real to string\n");
	if(wholep >= 10) {
		while(wholep >= 10) {
			num /= 10;
			fpoint--;
			wholep = num;
		}
	}
	else if(wholep == 0) {
		while(wholep == 0) {
			num *= 10;
			fpoint++;
			wholep = num;
		}
	}
	//printf("Number in scientific notation %lf, floating point moved %s %d positions\n", num, fpoint >= 0 ? "left" : "right", fpoint);
	
	counter = 8 - fpoint;
	i=0;
	while(i < counter) {
		if(stack_top == stack_size) {
			stack_size += 10;
			str = realloc(str, (stack_size+2) * sizeof(char));
		}
		if(i-1 == fpoint) {
			str[stack_top] = '.';
		}
		else {
			str[stack_top] = (int) num + '0';
			num -= (int) num;
			num *= 10;
			//printf("Num after run %d - %lf\n", i, num);
		}
		i++;
		stack_top++;
	}
	counter = 0;
	str[stack_top] = 0;
	
	return str; 
}

char* itoa(int num) {
	//printf("Converting num to str\n");
	int stack_size = 5;
	int stack_top = 0, i;
	char *stack = malloc(stack_size * sizeof(char));	
	char* str = malloc((stack_size+1) * sizeof(char));
	while(num > 0) {
		if(stack_top == stack_size) {
			stack_size += 5;
			stack = realloc(stack, stack_size * sizeof(char));
			str = realloc(str, (stack_size+1) * sizeof(char));
		}
		//printf("digit is %d\n", num % 10);
		stack[stack_top] = (num % 10) + '0';
		num /= 10;
		stack_top++;
	}
	i=0;
	for(; stack_top > 0 ; stack_top--) {
		str[i] = stack[stack_top-1];
		i++;
	}
	str[i] = 0;
	free(stack);
	return str;
}

int fprintf(FILE* stream, const char* format, ...) {
	int fd = fileno(stream);
	int buff_size = 128;
	int buff_fill = 0;
	char buff[128];
	
	va_list args;
	va_start(args, format);
	
	for(int i=0; format[i] != '\0'; i++) {
		buff[buff_fill] = format[i];
		buff_fill++;
		if(format[i] == '%') {
			write(fd, buff, buff_fill-1); 
			buff_fill = 0;
			switch(format[i+1]) {
				case 'd': 
				{	
					//printf("found num\n");
					int num = va_arg(args, int);
					char *strnum = itoa(num);
					//printf(strnum);
					write(fd, strnum, strlen(strnum));
					free(strnum);
					i++;
					break;
				}
				case 'f': 
				{
					//printf("Found real\n");
					float num = va_arg(args, double);
					char *strnum = rtoa(num);
					
					write(fd, strnum, strlen(strnum));
					free(strnum);
					i++;
					break;
				}
				case 'c':
				{
					char c = va_arg(args, int);
					write(fd, &c, 1);
					i++;
					break;
				}
				case 's': 
				{
					char *str = va_arg(args, char*);
					write(fd, str, strlen(str));
					i++;
					break;
				}
				case '%':
				{
					char c = '%';
					write(fd, &c, 1);
					i++;
					break;
				}
				default:
					break;
			}
		}
		if(buff_fill == buff_size || format[i+1] == 0) {
			write(fd, buff, buff_fill); 
			buff_fill = 0;
		}
			
	}
	return 0;
}

int main() {
	printf("%f\n", 6.12);
	fprintf(stdout, "Hello, %d %f world! %% %s\n", 5, 6.12, "brat");
	return 0;
}
