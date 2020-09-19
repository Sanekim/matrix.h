#include <stdio.h>
#include "matrix.h"

int main() {
	Matrix *A, *B, *C;

	A = newMatrix(3, 3);
	B = newMatrix(3, 3);

	inputMatrix(A);
	inputMatrix(B);

	C = mulMatrix(A, B);

	printMatrix(C);

	scanf_s(" ");
}