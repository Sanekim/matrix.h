#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fraction.h"

struct Matrix {
	int row, column;
	Fraction **data;
}typedef(Matrix);

Matrix *newMatrix(int, int);
void deleteMatrix(Matrix *);

void inputMatrix(Matrix *);
void printMatrix(Matrix *);

Matrix *addMatrix(Matrix *, Matrix *);
Matrix *subMatrix(Matrix *, Matrix *);
Matrix *kMatrix(Fraction, Matrix *);
Matrix *mulMatrix(Matrix *, Matrix *);

void swapRows(Matrix *, int, int);
void mulRow(Matrix *, int, Fraction);
void addMulRow(Matrix *, int, int, Fraction);

void gaussianElim(Matrix *);
void gaussJordanElim(Matrix *);