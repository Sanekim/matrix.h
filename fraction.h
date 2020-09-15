#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int gcd(int, int);

struct Fraction {
	int numerator;
	int denominator;
}typedef(Fraction);

Fraction fraction(int, int);

Fraction inputFraction();
void printFraction(Fraction);
double toDouble(Fraction);

Fraction reduceFraction(Fraction);
bool isReduced(Fraction);

Fraction absFraction(Fraction);
int compareFraction(Fraction, Fraction);

Fraction addFraction(Fraction, Fraction);
Fraction subFraction(Fraction, Fraction);
Fraction mulFraction(Fraction, Fraction);
Fraction reciprocal(Fraction);
Fraction divFraction(Fraction, Fraction);