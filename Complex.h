#ifndef COMPLEXH
#define COMPLEXH

#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>

using namespace std;

#define PI 3.14159265
#define toDegree(rad) rad*180.0/PI
#define toRadian(deg) deg*PI/180.0

class Complex{
	double real,img;
public:
	Complex();
	Complex(double);
	Complex(double,double);
	Complex(string);

	void setReal(double);
	void setImaginary(double);
	double getReal();
	double getImaginary();

	double magnitude();
	double phase();

	Complex operator+(Complex&);
	Complex operator-(Complex&);
	Complex operator*(Complex&);
	Complex operator/(Complex&);
	Complex operator^(int);

	static Complex rand();

	friend Complex sin(Complex&);
	friend Complex cos(Complex&);

	friend ostream& operator<<(ostream& out,Complex& a);
};
#endif