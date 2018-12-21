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

  return duration;
}


void vinogradMultiplyGetFactor(Matrix *result, Matrix *A, Matrix *B, \
  const int start_row, const int finish_row,\
   int* rowFactor, int* columnFactor) {

  int n = A->GetRows(), m = B->GetColumns(), l = A->GetColumns();

	for(int i = start_row; i < finish_row; i++)
		rowFactor[i] = 0;

  for(int i = start_row; i < finish_row; i++)
  	columnFactor[i] = 0;

	for(int i = start_row; i < finish_row; i++) // 2 + size(2 + ...)
		for(int j = 0; j < l/2; j++) //3 + size/2*(3 + ...)
			rowFactor[i] += A->GetData(i,2*j)*A->GetData(i, 2*j+1); // 1+1+1+1+3+1+4 = 12


	for(int i = start_row; i < finish_row; i++) // 2 + size(2 + ...)
		for(int j = 0; j < l/2; j++) //3 + size/2*(3 + ...)
			columnFactor[i] += B->GetData(2*j, i) * B->GetData(2*j+1, i); // 1+1+1+1+3+1+4 = 12
}

void vinogradMultiplyOneThread(Matrix *result, Matrix *A, Matrix *B,\
   const int start_row, const int finish_row,\
   int* rowFactor,int* columnFactor) {

  int n = A->GetRows(), m = B->GetColumns(), l = A->GetColumns();

	for(int i = start_row; i < finish_row; i++) //2 + size(2 + ...)
		for(int j = 0; j < m; j++) //2 + size(2 + ...)
		{
			result->SetData(i,j, -rowFactor[i] - columnFactor[j]); // 2+1+1+1+1+1=7
			for(int k = 0; k < l/2; k++){ //3 + size/2*(3 + ...)
        result->SetData(i,j, result->GetData(i,j) + \
        (A->GetData(i,2*k) + B->GetData(2*k+1,j))*(A->GetData(i,2*k+1) + B->GetData(2*k,j)));
			}//2+1+2+1+3+1+4+1+4+1+3 = 23
		}

	if(l%2 == 1) //2
		for(int i =start_row; i < finish_row; i++) // 2 + size*(2 + ...)
			for(int j = 0; j < m; j++) // 2 + size*(2 + ...)
				result->SetData(i,j, result->GetData(i,j) + A->GetData(i,l-1)*B->GetData(l-1,j));
}

double vinogradMultiplyThreads(Matrix &result, Matrix &A, Matrix &B, const int count_of_threads)
{

  //printf("INSIDE PRINT\n");
  //result.Print();
  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  std::vector<std::thread> threadVector;

  int* rowFactor = new int[A.GetRows()];
  int* columnFactor = new int[B.GetColumns()];

  int step = A.GetColumns()*1.0/count_of_threads;
  for(int i = 0; i < count_of_threads-1; i++) {
    //printf("step = %d; %d\n", step, step*(i+1)-1);
    threadVector.push_back(std::thread(vinogradMultiplyGetFactor, &result, &A, &B, step*i, step*(i+1), rowFactor, columnFactor));
  }
  threadVector.push_back(std::thread(vinogradMultiplyGetFactor, &result, &A, &B, (count_of_threads-1)*step, A.GetColumns()-1, rowFactor, columnFactor));

  for (std::thread& thread : threadVector) {
      if (thread.joinable()) {
          thread.join();
      }
  }
  threadVector.clear();
/*
  for(int i = 0; i < A.GetRows(); i++)
    printf("%d ", rowFactor[i]);
  printf("\n");
  for(int i = 0; i < B.GetColumns(); i++)
    printf("%d ", columnFactor[i]);
  printf("\n");
*/
  //printf("INSIDE PRINT\n");
  //result.Print();

  // ACTUALLY COUNTING RES MATRIX
  for(int i = 0; i < count_of_threads-1; i++) {
    threadVector.push_back(std::thread(vinogradMultiplyOneThread, &result, &A, &B, step*i, step*(i+1), rowFactor, columnFactor));
  }
  threadVector.push_back(std::thread(vinogradMultiplyOneThread, &result, &A, &B, (count_of_threads-1)*step, A.GetColumns()-1, rowFactor, columnFactor));

  for (std::thread& thread : threadVector) {
      if (thread.joinable()) {
          thread.join();
      }
  }
  threadVector.clear();

  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  double duration = duration_cast<microseconds>( t2 - t1 ).count();

  printf("Time is %f\n", duration/1000000);

  delete rowFactor;
  delete columnFactor;

  return duration;
}


//******************************************************************************

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
