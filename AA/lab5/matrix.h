#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
	Matrix(int rows, int columns);
	//Matrix(int rows, int columns, int randmax);
	~Matrix();

	void FillByRandomData();
	void FillByZero();

	int GetRows();
  int GetColumns();

	int GetData(int i, int j);
	void SetData(int i, int j, int value);
  void Print();

private:
	int rows, columns;
	int **data;

};

//Matrix casualMultiply(Matrix A, Matrix B);
double casualMultiplyThreads(Matrix &result, Matrix &A, Matrix &B, const int count_of_threads);
double vinogradMultiplyThreads(Matrix &result, Matrix &A, Matrix &B, const int count_of_threads);

#endif //MATRIX_H
