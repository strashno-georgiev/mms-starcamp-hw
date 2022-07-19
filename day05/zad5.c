#include <stdio.h>
#include <stdint.h>
int onesCount(uint64_t bitfield) {
	int count = 0;
	for(int i=0; i < sizeof(uint64_t) * CHAR_BIT; i++) {
		count += !!((bitfield >> i) & 1);
	}
	return count;
}
int main() {

}
