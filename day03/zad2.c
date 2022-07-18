#include <stdio.h>
#include <math.h>

// build-in compare operator
int floatCompare1(float a, float b){
    return a == b;
}

// fixed epsilon
int floatCompare2(float a, float b){
    return fabs(a - b) < 1.0e-5f;
}

// adaptive epsilon
int floatCompare3(float a, float b){
    return fabs(a - b) < 1.0e-5f * fmax(fabs(a), fabs(b));
}
// build-in compare operator
int doubleCompare1(double a, double b){
    return a == b;
}

// fixed epsilon
int doubleCompare2(double a, double b){
    return fabs(a - b) < 1.0e-5;
}

// adaptive epsilon
int doubleCompare3(double a, double b){
    return fabs(a - b) < 1.0e-5 * fmax(fabs(a), fabs(b));
}

#define NUM 5
int main(void){
    float a[NUM] = {1000.0f * 0.1f, 200.0f, 1100.0f};
    float b[NUM] = {0.0f, 49.0f * 4.0f + 4.0f};
    double da[NUM] = {1000.0 * 0.1, 200.0, 1100.0};
    double db[NUM] = {0.0, 49.0 * 4.0 + 4.0};
    for (int i = 0; i < 1000; i++, b[0] += 0.1f) {
    	b[2] += 1.1f;
    	db[0] += 0.1;
    	db[2] += 1.1;
    }
    for(int i=0; i < NUM; i++) {
    	printf("%f\n", a[i]);
    	printf("Float:\n");
		if (floatCompare1(a[i], b[i])){
		    printf("==: Equals\n");
		} else {
		    printf("==: Not equals\n");
		}
		if (floatCompare2(a[i], b[i])){
		    printf("fixed E: Equals\n");
		} else {
		    printf("fixed E: Not equals\n");
		}
		if (floatCompare3(a[i], b[i])){
		    printf("Adaptive E: Equals\n");
		} else {
		    printf("Adaptive E: Not equals\n");
		}
		
    	printf("Double:\n");		
		if (doubleCompare1(da[i], db[i])){
		    printf("==: Equals\n");
		} else {
		    printf("==: Not equals\n");
		}
		if (doubleCompare2(da[i], db[i])){
		    printf("fixed E: Equals\n");
		} else {
		    printf("fixed E: Not equals\n");
		}
		if (doubleCompare3(da[i], db[i])){
		    printf("Adaptive E: Equals\n");
		} else {
		    printf("Adaptive E: Not equals\n");
		}
	}
}
   
