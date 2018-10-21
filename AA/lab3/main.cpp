#include <cstdio>

//#include "matrix_func.h"
#include "get_time.h"

//#define SIZE 1000
#define TIMES 10

int main() {

	for(int i = 0; i < 20; i++) {
		int SIZE = 100 + i*100;

		double t1, t2, restimeMult = 0, restimeVin = 0, restimeVinUpgr = 0;

		for(int j = 0; j < TIMES; j++) {
			
			t1 =  getCPUTime( );
			
			t2 =  getCPUTime( );

			restimeMult += (t2-t1);

		}

		printf("Proc time for %d elements casual mult :\n%f\n", SIZE, restimeMult/TIMES);
		printf("Proc time for %d elements Vinograd mult :\n%f\n", SIZE, restimeVin/TIMES);
		printf("Proc time for %d elements upgrade Vinograd mult:\n%f\n",SIZE, restimeVinUpgr/TIMES);
		puts("");

	}
}
