#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fraction.h"

struct FracMatrix {
	int row, column;
	Fraction **data;
}typedef(FracMatrix);

FracMatrix *newFracMatrix(int, int);
void deleteFracMatrix(FracMatrix *);

void inputFracMatrix(FracMatrix *);
void printFracMatrix(FracMatrix *);

void fracSwapRows(FracMatrix *, int, int);
void fracMulRow(FracMatrix *, int, Fraction);
void fracAddMulRow(FracMatrix *, int, int, Fraction);

void fracGaussianElim(FracMatrix *);
void fracGaussJordanElim(FracMatrix *);

FracMatrix *fracInverse(FracMatrix *);

FracMatrix *FracLUDecomposition(FracMatrix *);
