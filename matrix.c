#include "fraclinalg.h"
#include "fraction.h"

FracMatrix *newFracMatrix(int row, int column) {
	FracMatrix *tempFracMatrix = (FracMatrix *)malloc(sizeof(FracMatrix));
	Fraction **tempData = (Fraction **)malloc(sizeof(Fraction *) * row);
	int i;

	tempData[0] = (Fraction *)malloc(sizeof(Fraction) * row * column);

	for (i = 1; i < row; i++) tempData[i] = tempData[i - 1] + column;

	tempFracMatrix->row = row;
	tempFracMatrix->column = column;
	tempFracMatrix->data = tempData;

	return tempFracMatrix;
}

void deleteFracMatrix(FracMatrix *A) {
	free(A->data[0]);
	free(A->data);
	free(A);

}

void inputFracMatrix(FracMatrix *A) {
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

void printFracMatrix(FracMatrix *A) {
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

void fracSwapRows(FracMatrix *A, int r1, int r2) {
	int i;
	Fraction temp;

	for (i = 0; i < A->column; i++) {
		temp = A->data[r1][i];
		A->data[r1][i] = A->data[r2][i];
		A->data[r2][i] = temp;
	}
}

void fracMulRow(FracMatrix *A, int row, Fraction f) {
	int i;
	
	for (i = 0; i < A->column; i++) {
		A->data[row][i] = mulFraction(A->data[row][i], f);
	}
}

void fracAddMulRow(FracMatrix *A, int r1, int r2, Fraction f) {
	int i;
	Fraction f1, f2;

	for (i = 0; i < A->column; i++) {
		f1 = A->data[r1][i];
		f2 = A->data[r2][i];

		A->data[r1][i] = addFraction(f1, mulFraction(f2, f));
	}
}

void fracGaussianElim(FracMatrix *A) {
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

		else if(i_notzero != pivotR) fracSwapRows(A, pivotR, i_notzero);

		for (i = pivotR + 1; i < m; i++) {
			k = divFraction(A->data[i][pivotC], A->data[pivotR][pivotC]);

			k = mulFraction(k, fraction(-1, 1));

			fracAddMulRow(A, i, pivotR, k);
		}

		pivotR++;
		pivotC++;
	}
}

void fracGaussJordanElim(FracMatrix *A) {
	int i, j, l, m, n;
	Fraction k;

	m = A->row;
	n = A->column;

	fracGaussianElim(A);

	for (i = m - 1; i >= 0; i--) {
		j = 0;

		while (toDouble(A->data[i][j]) == 0 && j < n) j++;

		if (j == n) continue;

		fracMulRow(A, i, reciprocal(A->data[i][j]));

		for (l = 0; l < i; l++) {
			if (A->data[l][j].numerator) {
				k = divFraction(A->data[l][j], A->data[i][j]);

				k = mulFraction(k, fraction(-1, 1));

				fracAddMulRow(A, l, i, k);
			}
		}
	}
}

FracMatrix *fracInverse(FracMatrix *A) {

}

FracMatrix *fracLUDecomposition(FracMatrix *A) {

}
