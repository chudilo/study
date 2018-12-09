#include <time.h>
#include <stdlib.h>
#include <vector>
#include <exception>
#include <random>
#include <stdio.h>
#include <thread>

#include "matrix.h"

int main() {

	printf("start\n");
	//create 2 matrix
	int matrix_size = 3;
	Matrix A(matrix_size, matrix_size);
	Matrix B(matrix_size, matrix_size);

	A.Print();
	B.Print();

	//for 1 to 20 threads//
	printf("Time for CASUAL and VINOGRAD multiply\n");

	for(int i = 0; i < 20; i++)
		printf("|  %d  |  %d  |\n",0,0);

	//return time - multiply casual
	//return time - multiply vinograd


	return 0;
}