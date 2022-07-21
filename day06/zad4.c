#include <stdarg.h>
#include <stdio.h>

unsigned countOnes(int mask) {
	int cnt = 0;
	while(mask) {
		cnt += mask & 1;
		mask = mask >> 1;
	}
	return cnt;
}

unsigned int bitsNCount(unsigned int count, unsigned int bitscnt, ...) {
	va_list args;
	va_start(args, bitscnt);
	int matches = 0, mask=0;
	for(int i=0;i < count; i++) {
		mask = va_arg(args, int);
		if(countOnes(mask) == bitscnt) {
			matches++;
		}
	}
	va_end(args);
	return matches;
} 


int main() {
	printf("%d\n", bitsNCount(4, 2, 0x0a, 0xff, 0, 3));
}
