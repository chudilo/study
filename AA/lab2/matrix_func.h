

int** matrixCreate(int rows, int columns);
void matrixFree(int** matrixPtr, int rows);
void matrixPrint(int** matrixPtr, int rows, int columns);
void matrixFillRand(int** matrixPtr, int rows, int columns);
void matrixFillZero(int** matrixPtr, int rows, int columns);

void matrixMult(int **first, int **second, int **result, int size);
void matrixMultVinograd(int **first, int **second, int **result, int size);
void matrixMultVinogradUpgr(int **first, int **second, int **result, int size);