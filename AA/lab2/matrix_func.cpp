#include "matrix_func.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

int **matrixCreate(int rows, int columns) {
	int **matrixPtr = (int**)malloc(rows*sizeof(int));

	for(int i = 0; i < rows; i++)
		matrixPtr[i] = (int*)malloc(columns*sizeof(int));

	return matrixPtr;
}


void matrixFree(int ** matrixPtr, int rows) {
	for(int i = 0; i < rows; i++)
		free(matrixPtr[i]);

	free(matrixPtr);
}

int init_seed() {
	std::srand(std::time(0)); //use current time as seed for random generator
  	return 0;
}

void matrixFillRand(int** matrixPtr, int rows, int columns) {
 	static int seed = init_seed(); 
    for(int i = 0; i < rows; i++) 
    	for(int j = 0; j < columns; j++)
    		matrixPtr[i][j] =  std::rand()%3;
}

void matrixFillZero(int** matrixPtr, int rows, int columns) {
 	for(int i = 0; i < rows; i++) 
    	for(int j = 0; j < columns; j++)
    		matrixPtr[i][j] =  0;

}

void matrixPrint(int ** matrixPtr, int rows, int columns) {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < rows; j++)
			printf("%-4.1d", matrixPtr[i][j]);
		puts("");
	}
	puts("");
}

void matrixMult(int **first, int **second, int **result, int size) {

	for(int i = 0; i < size; i++) // 2 + size*(2 + ...)
		for(int j = 0; j < size; j++) // 2 + size*(2 + ...)
			for(int k = 0; k < size; k++) // 2 + size*(2 + ...)
				result[i][j] = result[i][j] + first[i][k] * second[k][j]; // 2+1+2+1+2+1+2 = 11
}


void matrixMultVinograd(int **first, int **second, int **result, int size) {
  
	int *multH = (int*)malloc(size*sizeof(int));	
	int* multV = (int*)malloc(size*sizeof(int));
	
	for(int i = 0; i < size; i++)
	{
		multH[i] = 0;
		multV[i] = 0;
	}
	
	for(int i = 0; i < size; i++){ // 2 + size(2 + ...)
		for(int j = 0; j < size/2; j++){ //3 + size/2*(3 + ...) 
			multH[i] = multH[i] + first[i][2*j]*first[i][2*j+1]; // 1+1+1+1+3+1+4 = 12
		}
    }

	for(int i = 0; i < size; i++){ // 2 + size(2 + ...)
		for(int j = 0; j < size/2; j++) //3 + size/2*(3 + ...)
			multV[i] = multV[i] + second[2*j][i]*second[2*j+1][i]; // 1+1+1+1+3+1+4 = 12
    }
	for(int i = 0; i < size; i++) //2 + size(2 + ...)
		for(int j = 0; j < size; j++) //2 + size(2 + ...)
		{
			result[i][j] = -multH[i]- multV[j]; // 2+1+1+1+1+1=7 
			for(int k = 0; k < size/2; k++){ //3 + size/2*(3 + ...)
				result[i][j] = result[i][j] + \
(first[i][2*k] + second[2*k+1][j])*(first[i][2*k+1] + second[2*k][j]);
			}//2+1+2+1+3+1+4+1+4+1+3 = 23
		}
	
	if(size%2 == 1) //2
		for(int i =0; i< size; i++) // 2 + size*(2 + ...)
			for(int j = 0; j< size; j++) // 2 + size*(2 + ...)
				result[i][j] = result[i][j] + first[i][size-1]*second[size-1][j]; //2+1+2+1+3+1+3 = 13
} 


void matrixMultVinogradUpgr(int **first, int **second, int **result, int size){
  
	int *multH = (int*)malloc(size*sizeof(int));	
	int* multV = (int*)malloc(size*sizeof(int));
	
	int hsize = size/2;
	
	for(int i = 0; i < size; i++){
		multH[i] = 0;
		for(int j = 0; j < hsize; j++)
			multH[i] += first[i][2*j]*first[i][2*j+1];
	}

	for(int i = 0; i < size; i++){
		multV[i] = 0;
		for(int j = 0; j < hsize; j++)
			multV[i] += second[2*j][i]*second[2*j+1][i];
	}
	
	int buf;
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++){
			buf = 0 -multH[i]- multV[j];
			for(int k = 0; k < hsize; k++)
				buf += (first[i][2*k] + second[2*k+1][j])*(first[i][2*k+1] + second[2*k][j]);	
			
			result[i][j] = buf;
		}
	
	if(size%2 == 1)
		for(int i =0; i< size; i++)
			for(int j = 0; j< size; j++)
				result[i][j] += first[i][size-1]*second[size-1][j];
}