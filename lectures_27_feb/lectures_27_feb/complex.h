#pragma once

class Complex
{
public:
	double Re;
	double Im;

	Complex() :Re(0), Im(0) {}
	Complex(double Re, double Im) : Re(Re), Im(Im) {}

	double abs();
	Complex add(Complex c);
	Complex& addEq(Complex c);
	//static Complex add(Complex c1, Complex c2);
};

void print(Complex c);