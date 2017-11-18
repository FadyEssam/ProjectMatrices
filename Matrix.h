#ifndef MATRIXHH
#define MATRIXHH
#include<iostream>
#include<string>
#include "Complex.h"
using namespace std;

class Matrix
{
private:
	int rows, columns;
	Complex** elements;
	string name;

public:
	//essential
	Matrix();
	Matrix (const Matrix &m);
	~Matrix();
	Matrix(int r, int c);
	Matrix(int r, int c, string n);
	void initialize(Complex value);
	void destroy();
	void setRows(int r);
	void setColumns(int c);
	void setName(string s);
	int getColumns() const;
	int getRows() const;
	string getName() const;
	void setConstant(Complex value);
	Complex getConstant() const;
	int isConstant() const;
	//printing
	void print();


	//changing values
	void setElement(int r, int c, Complex value);
	Complex* operator[](int r) const;
	void stickToSide(const Matrix & m);
	void stickToBottom(const Matrix & m);
	

	//Arithmatics
	Matrix operator^(const Matrix & m);
	Matrix operator^(Complex value);
	Matrix operator+(const Matrix & m);
	void operator=(const Matrix & m);
	Matrix operator-(const Matrix & m);
	Matrix operator*(const Matrix & m);
	Complex determinant() const;
	Matrix inverse() const;
	Matrix transbose() const;
	Matrix operator/(const Matrix & m);
	Matrix dotDivision(Complex value);
	Matrix dotProduct(Complex value);
	Matrix operator-(Complex value);
	Matrix operator+(Complex value);
	Matrix dotProduct(const Matrix & m);
	Matrix dotDivision(const Matrix & m);
	Matrix dotPower(const Matrix & m);
	Matrix dotPower(Complex value);
	Matrix powerFraction(Complex value);
	Matrix msqrt();
	Matrix msin();
	Matrix mcos();
	Matrix mtan();
	int isZeroMatrix() const;
	Complex advancedDeterminant() const;
	Complex abs(Complex val) const;




	//Helping functions
private:
	Matrix removeColRow(int r, int c)const;

};

ostream& operator<< (ostream & o, Matrix m);
 Matrix zeros(int r, int c);
 Matrix ones(int r, int c);
 Matrix rand(int r, int c);
 Matrix eye(int r, int c);
#endif