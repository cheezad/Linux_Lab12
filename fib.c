// **Configuration**
#define ROUNDS 100
#define D_GETTIME 1
// **Configuration**
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

static double GETTIME(){
	struct timespec ts;
        double sec;
        clock_gettime(CLOCK_REALTIME, &ts);
        sec = ts.tv_nsec;
        sec /= 1e9;
        sec += ts.tv_sec;
        return sec;
}


int main(int argc, char** argv)
{
    double measure_gettime = 0;
    uint64_t fib[50] = {0};
#if D_GETTIME
    double t1 = GETTIME();
#endif

    for(int r = 0; r < ROUNDS; r++) {
	for(int i = 0 ; i < 50 ; i++){
		if(i == 0 || i == 1) fib[i] = 1;
		else fib[i] = fib[i-1] + fib[i-2];
	}	
    }
    #if D_GETTIME
    double time_s = GETTIME()-t1;
    measure_gettime += time_s;
#endif
    for(int i = 0; i < 50; i++) {
        printf("%lu ", fib[i]);
    }
    printf("\n");
    printf(" %.9lf | ", (double)measure_gettime/ROUNDS);
    printf("\n");
    return 0;
}
