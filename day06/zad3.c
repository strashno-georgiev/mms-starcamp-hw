#include <stdio.h>
#include <stdint.h>
#define TINT 1
#define TCHAR 2
#define TDOUBLE 3
#define TFLOAT 4
#define TUINT8 5
#define TUINT16 6
#define TUINT32 7
#define TUINT64 8 
void printValue(void* valuePtr, uint8_t flag) {
	switch(flag) {
		case TINT:
			printf("%d\n", *(int*)valuePtr);
			break;
		case TCHAR:
			printf("%c\n", *(char*)valuePtr);
			break;
		case TDOUBLE:
			printf("%lf\n", *(double*)valuePtr);
			break;
		case TFLOAT:
			printf("%f\n", *(float*)valuePtr);
			break;
		case TUINT8:
			printf("%d\n", *(uint8_t*)valuePtr);
			break;
		case TUINT16:
			printf("%d\n", *(uint16_t*)valuePtr);
			break;
		case TUINT32:
			printf("%d\n", *(uint32_t*)valuePtr);
			break;
		case TUINT64:
			printf("%d\n", *(uint64_t*)valuePtr);
			break;																		
	}
}

int main() {
	float a = 4.78;
	printValue((void*)&a, TFLOAT);
}
