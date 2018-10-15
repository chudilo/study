#include <cstdio>

#include "matrix_func.h"
#include "get_time.h"

//#define SIZE 1000
#define TIMES 10

int main() {

	for(int i = 0; i < 20; i++) {
		int SIZE = 100 + i*100;

		int **matrA = matrixCreate(SIZE,SIZE);
		int **matrB = matrixCreate(SIZE,SIZE);
		int **resMatr = matrixCreate(SIZE,SIZE);

		double t1, t2, restimeMult = 0, restimeVin = 0, restimeVinUpgr = 0;

		for(int j = 0; j < TIMES; j++) {
			matrixFillRand(matrA, SIZE, SIZE);
			matrixFillRand(matrB, SIZE, SIZE);

			matrixFillZero(resMatr, SIZE, SIZE);

			t1 =  getCPUTime( );
			matrixMult(matrA,matrB,resMatr,SIZE);
			t2 =  getCPUTime( );
			//matrixPrint(resMatr,SIZE,SIZE);
			restimeMult += (t2-t1);


			matrixFillZero(resMatr, SIZE, SIZE);

			t1 =  getCPUTime( );
			matrixMultVinograd(matrA,matrB,resMatr,SIZE);
			t2 =  getCPUTime( );
			//matrixPrint(resMatr,SIZE,SIZE);
			restimeVin += (t2-t1);



			matrixFillZero(resMatr, SIZE, SIZE);

			t1 =  getCPUTime( );
			matrixMultVinogradUpgr(matrA,matrB,resMatr,SIZE);
			t2 =  getCPUTime( );
			//matrixPrint(resMatr,SIZE,SIZE);
			restimeVinUpgr += (t2-t1);


		}

		printf("Proc time for %d elements casual mult :\n%f\n", SIZE, restimeMult/TIMES);
		printf("Proc time for %d elements Vinograd mult :\n%f\n", SIZE, restimeVin/TIMES);
		printf("Proc time for %d elements upgrade Vinograd mult:\n%f\n",SIZE, restimeVinUpgr/TIMES);
		puts("");
		
		matrixFree(matrA,SIZE);
		matrixFree(matrB,SIZE);
		matrixFree(resMatr,SIZE);
	}
}
