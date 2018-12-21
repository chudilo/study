#include <time.h>
#include <chrono>
#include <iostream>


#include <stdlib.h>
#include <vector>
#include <exception>
#include <random>
#include <stdio.h>
#include <thread>
#include "matrix.h"

using namespace std;
using namespace std::chrono;

//int start_row, int finish_row, Matrix A, Matrix B, Matrix result
void casualMultiplyOneThread(Matrix *result, Matrix *A, Matrix *B, const int start_row, const int finish_row) {
  int r = B->GetColumns(), m = B->GetRows();

  for(int i = start_row; i < finish_row+1; i++)
    for(int j = 0; j < m; j++)
      for(int k = 0; k < r; k++)
        result->SetData(i, j, result->GetData(i,j) + A->GetData(i,k)*B->GetData(k,j));
        //a[i][j] = A[i][k]*B[k][j];

  //printf("start_row = %d, finish_row = %d\n", start_row, finish_row);
}

double casualMultiplyThreads(Matrix &result, Matrix &A, Matrix &B, const int count_of_threads)
{
  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  std::vector<std::thread> threadVector;

  int step = A.GetColumns()*1.0/count_of_threads;
  for(int i = 0; i < count_of_threads-1; i++) {
    //printf("step = %d; %d\n", step, step*(i+1)-1);
    threadVector.push_back(std::thread(casualMultiplyOneThread, &result, &A, &B, step*i, step*(i+1)-1));
  }
  threadVector.push_back(std::thread(casualMultiplyOneThread, &result, &A, &B, (count_of_threads-1)*step, A.GetColumns()-1));

  for (std::thread& thread : threadVector) {
      if (thread.joinable()) {
          thread.join();
          //printf("thread\n");
      }
  }

  threadVector.clear();

  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  double duration = duration_cast<microseconds>( t2 - t1 ).count();

  printf("Time is %f\n", duration/1000000);

  return 0;
}

int getRandSeed() {
  srand(time(NULL));
}

void Matrix::FillByRandomData()
{
    static int not_used = getRandSeed();
    int rand_max = 10;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            data[i][j] = rand() % rand_max;
        }
    }
}

void Matrix::FillByZero() {
  for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
          data[i][j] = 0;
      }
  }
}

int Matrix::GetData(int i, int j) {
  return  data[i][j];
}

void Matrix::SetData(int i, int j, int value) {
  data[i][j] = value;
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
