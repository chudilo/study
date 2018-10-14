#include <cstdio>

#include "matrix_func.h"
#include "get_time.h"

#define SIZE 3

int main() {

	for(int i = 0; i < 20; i++) {
		int **matrA = matrixCreate(SIZE,SIZE);
		matrixFillRand(matrA, SIZE, SIZE);
		//matrixPrint(matrA, SIZE, SIZE);

		int **matrB = matrixCreate(SIZE,SIZE);
		matrixFillRand(matrB, SIZE, SIZE);
		//matrixPrint(matrB, SIZE, SIZE);

		double t1, t2, restime;

		int **resMatr = matrixCreate(SIZE,SIZE);

		matrixFillZero(resMatr, SIZE, SIZE);
		restime = 0;
		//t1 = 
		matrixMult(matrA,matrB,resMatr,SIZE);
		//t2 =
		//restime = (t2-t1)/1000;
		//matrixPrint(resMatr,SIZE,SIZE);

		matrixFillZero(resMatr, SIZE, SIZE);
		restime = 0;
		//t1 =
		matrixMultVinograd(matrA,matrB,resMatr,SIZE);
		//t2 =
		//restime = (t2-t1)/1000;		
		//matrixPrint(resMatr,SIZE,SIZE);

		matrixFillZero(resMatr, SIZE, SIZE);
		restime = 0;
		//t1 =
		matrixMultVinogradUpgr(matrA,matrB,resMatr,SIZE);
		//t2 =
		//restime = (t2-t1)/1000;
		//matrixPrint(resMatr,SIZE,SIZE);

		matrixFree(matrA,SIZE);
		matrixFree(matrB,SIZE);
		matrixFree(resMatr,SIZE);
	}


}