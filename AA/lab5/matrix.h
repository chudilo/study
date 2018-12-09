#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
	Matrix(int rows, int columns);
	//Matrix(int rows, int columns, int randmax);
	~Matrix();

	void FillByRandomData();

	int GetRows();
    int GetColumns();

    void Print();

private:
	int rows, columns;
	int **data;

};

#endif //MATRIX_H