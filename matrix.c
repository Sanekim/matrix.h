#include "matrix.h"
#include "fraction.h"

Matrix *newMatrix(int row, int column) {
	Matrix *tempMatrix = (Matrix *) malloc(sizeof(Matrix));
	Fraction **tempData = (Fraction **)malloc(sizeof(Fraction *) * row);
	int i;

	tempData[0] = (Fraction *)malloc(sizeof(Fraction) * row * column);

	for (i = 1; i < row; i++) tempData[i] = tempData[i - 1] + column;

	tempMatrix->row = row;
	tempMatrix->column = column;
	tempMatrix->data = tempData;

	return tempMatrix;
}

void deleteMatrix(Matrix *A) {
	free(A->data[0]);
	free(A->data);
	free(A);
}

void inputMatrix(Matrix *A) {
	int i, j, m, n, a;

	m = A->row;
	n = A->column;

	printf("Input matrix [%d * %d]\n", m, n);

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
		{
			scanf("%d", &a);
			A->data[i][j] = fraction(a, 1);
		}
	}
}

void printMatrix(Matrix *A) {
	int i, j, m, n;

	m = A->row;
	n = A->column;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) { 
			printFraction(A->data[i][j]);
			printf(" ");
		}

		printf("\n");
	}
}

Matrix *addMatrix(Matrix *A, Matrix *B) {
	int i, j;
	
	Matrix *C = newMatrix(A->row, A->column);

	for (i = 0; i < A->row; i++) {
		for (j = 0; j < A->column; j++) {
			C->data[i][j] = addFraction(A->data[i][j], B->data[i][j]);
		}
	}

	return C;
}

Matrix *subMatrix(Matrix *A, Matrix *B) {
	int i, j;

	Matrix *C = newMatrix(A->row, A->column);

	for (i = 0; i < A->row; i++) {
		for (j = 0; j < A->column; j++) {
			C->data[i][j] = subFraction(A->data[i][j], B->data[i][j]);
		}
	}

	return C;
}

Matrix *kMatrix(Fraction k, Matrix *A) {
	int i, j;

	Matrix *C = newMatrix(A->row, A->column);

	for (i = 0; i < A->row; i++) {
		for (j = 0; j < A->column; j++) {
			C->data[i][j] = mulFraction(k, A->data[i][j]);
		}
	}

	return C;
}

Matrix *mulMatrix(Matrix *A, Matrix *B) {
	int i, j, k;

	Matrix *C = newMatrix(A->row, B->column);

	for (i = 0; i < A->row; i++) {
		for (j = 0; j < B->column; j++) {
			C->data[i][j] = fraction(0, 1);
			for (k = 0; k < A->column; k++) {
				C->data[i][j] = 
					addFraction(
						C->data[i][j], 
						mulFraction(A->data[i][k], B->data[k][j])
					);
			}
		}
	}

	return C;
}

void swapRows(Matrix *A, int r1, int r2) {
	int i;
	Fraction temp;

	for (i = 0; i < A->column; i++) {
		temp = A->data[r1][i];
		A->data[r1][i] = A->data[r2][i];
		A->data[r2][i] = temp;
	}
}

void mulRow(Matrix *A, int row, Fraction f) {
	int i;
	
	for (i = 0; i < A->column; i++) {
		A->data[row][i] = mulFraction(A->data[row][i], f);
	}
}

void addMulRow(Matrix *A, int r1, int r2, Fraction f) {
	int i;
	Fraction f1, f2;

	for (i = 0; i < A->column; i++) {
		f1 = A->data[r1][i];
		f2 = A->data[r2][i];

		A->data[r1][i] = addFraction(f1, mulFraction(f2, f));
	}
}

void gaussianElim(Matrix *A) {
	int i, m, n;
	int pivotR = 0, pivotC = 0;
	int i_notzero;
	Fraction k;

	m = A->row;
	n = A->column;

	while (pivotR < m && pivotC < n) {
		i_notzero = pivotR;

		while (i_notzero < m && toDouble(A->data[i_notzero][pivotC]) == 0) i_notzero++;

		if (i_notzero == m) {
			pivotC++;
			continue;
		}

		else if(i_notzero != pivotR) swapRows(A, pivotR, i_notzero);

		for (i = pivotR + 1; i < m; i++) {
			k = divFraction(A->data[i][pivotC], A->data[pivotR][pivotC]);

			k = mulFraction(k, fraction(-1, 1));

			addMulRow(A, i, pivotR, k);
		}

		pivotR++;
		pivotC++;
	}
}

void gaussJordanElim(Matrix *A) {
	int i, j, l, m, n;
	Fraction k;

	m = A->row;
	n = A->column;

	gaussianElim(A);

	for (i = m - 1; i >= 0; i--) {
		j = 0;

		while (toDouble(A->data[i][j]) == 0 && j < n) j++;

		if (j == n) continue;

		mulRow(A, i, reciprocal(A->data[i][j]));

		for (l = 0; l < i; l++) {
			if (A->data[l][j].numerator) {
				k = divFraction(A->data[l][j], A->data[i][j]);

				k = mulFraction(k, fraction(-1, 1));

				addMulRow(A, l, i, k);
			}
		}
	}
}
