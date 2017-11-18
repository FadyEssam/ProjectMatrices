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

	Complex operator+(Complex);
	Complex operator-(Complex);
	Complex operator*(Complex);
	Complex operator/(Complex);
	Complex operator+=(Complex);
	Complex operator-=(Complex);
	Complex operator*=(Complex);
	Complex operator/=(Complex);
	Complex operator+(double a);
	Complex operator-(double a);
	Complex operator*(double a);
	Complex operator/(double a);
	Complex operator+=(double a);
	Complex operator-=(double a);
	Complex operator*=(double a);
	Complex operator/=(double a);
	Complex operator^(double a);
	char operator<(double a);
	char operator>(double a);
	char operator<(Complex a);
	char operator>(Complex a);
	Complex operator-();
	char operator==(Complex a);
	char operator==(double a);
	friend char operator==(double a, Complex b);
	char operator!=(Complex a);
	char operator!=(double a);
	friend char operator!=(double a, Complex b);
	friend Complex Round(Complex a);
	
	friend Complex Sqrt(Complex a);


	static Complex rand();

	friend Complex sin(Complex);
	friend Complex cos(Complex);
	friend Complex pow(Complex a, double p);
	friend Complex operator+(double a,Complex b);
	friend Complex operator-(double a,Complex b);
	friend Complex operator*(double a,Complex b);
	friend Complex operator/(double a,Complex b);
	friend int operator<(double a,Complex b);
	friend int operator>(double a,Complex b);

	friend ostream& operator<<(ostream& out,Complex a);
};
#endif