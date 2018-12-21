#include <stdio.h>
#include <time.h>

#include "matrix.h"

#define COUNT_OF_THREADS 8

int main() {

	printf("Algorythm Analisis; Program 5 - threading\n");
	//create 2 matrix
	int matrix_size = 1001;
	Matrix A(matrix_size, matrix_size);
	Matrix B(matrix_size, matrix_size);
	Matrix res(matrix_size, matrix_size);
	//A.Print();
	//B.Print();

	//for 1 to 20 threads//
	printf("Time for CASUAL and VINOGRAD multiply\n");

	double res_time;

	for(int i = 0; i < COUNT_OF_THREADS; i++) {
			res.FillByZero();
			//res.Print();
			printf("%d threads\n", i+1);
			res_time = casualMultiplyThreads(res, A, B, i+1);
			//res.Print();
	}

	for(int i = 0; i < COUNT_OF_THREADS; i++) {
			res.FillByZero();
			//res.Print();
			printf("%d threads\n", i+1);
			res_time = vinogradMultiplyThreads(res, A, B, i+1);
			//res.Print();
	}

			//puts("Hi");
	//return time - multiply casual
	//return time - multiply vinograd


	return 0;
}
