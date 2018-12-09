#include <time.h>
#include <stdlib.h>
#include <vector>
#include <exception>
#include <random>
#include <stdio.h>
#include <thread>
#include "matrix.h"

void Matrix::FillByRandomData()
{
    srand(time(nullptr));
    int rand_max = 10;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
        	//puts("");
            data[i][j] = rand() % rand_max;
        }
    }
}

int Matrix::GetRows() {
	return rows;
}

int Matrix::GetColumns(){
	return columns;
}

void Matrix::Print(){
	puts("");
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++)
			printf("%4.3d ", data[i][j]);
		printf("\n");
	}
	puts("");
}

Matrix::Matrix(int rows, int columns): rows(rows), columns(columns) {
	
	if(!(rows > 0 && columns > 0)){
		puts("Wrong matrix size");
		//return;
	}
	
	data = new int*[rows];
	//data = (int**)(malloc(sizeof(int*)*rows));

    for (int i = 0; i < rows; i++)
        data[i] = new int[columns];
	
    FillByRandomData();
}

Matrix::~Matrix(){
	for(int i = 0; i < rows; i++)
		delete data[i];
	delete data;
}