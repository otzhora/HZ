#include "complex.h"
#include <cmath>
#include <iostream>
using namespace std;

double Complex::abs()
{
	return sqrt(Re*Re + Im * Im);
}

Complex Complex::add(Complex c)
{
	return Complex(Re + c.Re, Im + c.Im);
}

Complex& Complex::addEq(Complex c)
{
	Re += c.Re;
	Im += c.Im;
	return *this;
}

void print(Complex c)
{
	cout << c.Re << "+" << c.Im << "i" << endl;
}