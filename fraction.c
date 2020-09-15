#include "fraction.h"

int gcd(int a, int b) {
	int r;

	//swap
	if (a < b) {
		r = a;
		a = b;
		b = r;
	}

	//gcd(x, 0) = x
	if (b == 0) return a;

	r = a % b;

	if (r == 0) return b;
	else return gcd(b, r);
}

Fraction _fraction(int a, int b) {
	Fraction tempFraction;

	tempFraction.numerator = a;
	tempFraction.denominator = b;

	return tempFraction;
}

Fraction fraction(int a, int b) {
	Fraction tempFraction;

	tempFraction = _fraction(a, b);

	return reduceFraction(tempFraction);
}

Fraction inputFraction() {
	int a, b = 0;

	scanf("%d/%d", &a, &b);

	if (b == 0) return fraction(a, 1);
	else return fraction(a, b);
}

void printFraction(Fraction f) {
	int a, b;

	a = f.numerator;
	b = f.denominator;

	if (b == 0) printf("NaN");
	else if (b == 1) printf("%d", a);
	else if (a == 0) printf("0");
	else printf("%d/%d", a, b);
}

double toDouble(Fraction f) {
	int a, b;
	double x;
	
	a = f.numerator;
	b = f.denominator;

	if (b == 0) return NAN;
	
	x = (double)a / b;
	return x;
}

Fraction reduceFraction(Fraction f) {
	int a, b, d;

	if (isReduced(f) == true) return f;

	a = f.numerator;
	b = f.denominator;
	d = gcd(abs(a), abs(b));

	a /= d; b /= d;

	if (b < 0) {
		b = -b;
		a = -a;
	}

	return _fraction(a, b);
}

bool isReduced(Fraction f) {
	int a, b;

	a = f.numerator;
	b = f.denominator;

	if (gcd(abs(a), abs(b)) == 1) return true;
	else return false;
}

Fraction absFraction(Fraction f) {
	int a, b;

	a = abs(f.numerator);
	b = abs(f.denominator);

	return fraction(a, b);
}

int compareFraction(Fraction f, Fraction g) {
	int a1, b1, a2, b2;
	float x, y;

	a1 = f.numerator;
	b1 = f.denominator;
	a2 = g.numerator;
	b2 = g.denominator;

	x = (float)a1 / b1;
	y = (float)a2 / b2;

	if (x == y) return 0;
	else if (x > y) return 1;
	else return -1;

}

Fraction addFraction(Fraction f, Fraction g) {
	int a1, b1, a2, b2;
	int a, b;

	a1 = f.numerator;
	b1 = f.denominator;
	a2 = g.numerator;
	b2 = g.denominator;

	a = a1 * b2 + a2 * b1;
	b = b1 * b2;

	return reduceFraction(fraction(a, b));
}

Fraction subFraction(Fraction f, Fraction g) {
	int a1, b1, a2, b2;
	int a, b;

	a1 = f.numerator;
	b1 = f.denominator;
	a2 = g.numerator;
	b2 = g.denominator;

	a = a1 * b2 - a2 * b1;
	b = b1 * b2;

	return reduceFraction(fraction(a, b));
}

Fraction mulFraction(Fraction f, Fraction g) {
	int a1, b1, a2, b2;
	int a, b;

	a1 = f.numerator;
	b1 = f.denominator;
	a2 = g.numerator;
	b2 = g.denominator;

	a = a1 * a2;
	b = b1 * b2;

	return reduceFraction(fraction(a, b));
}

Fraction reciprocal(Fraction f) {
	int a, b;

	a = f.numerator;
	b = f.denominator;

	return fraction(b, a);
}

Fraction divFraction(Fraction f, Fraction g) {

	return mulFraction(f, reciprocal(g));
}