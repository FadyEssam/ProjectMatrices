#ifndef MATRIXHH
#define MATRIXHH
#include<iostream>
#include<string>
#include <math.h>
using namespace std;

class Matrix
{
private:
	int rows, columns;
	double** elements;
	string name;


public:
	//essential
	Matrix();
	Matrix(int r, int c);
	Matrix(int r, int c, string n);
	void initialize(double value);
	//void Matrix(Matrix& m);
	void destroy();
	void setRows(int r);
	void setColumns(int c);
	void setName(string s);
	int getColumns();
	int getRows();
	string getName();
	void setConstant(double value);
	double getConstant();
	int isConstant();
	//printing
	void print();


	//changing values
	void setElement(int r, int c, double value);
	double* operator[](int r);


	//Arithmatics
	Matrix operator^(Matrix m);
	Matrix operator^(double value);
	Matrix operator+(Matrix m);
	void operator=(Matrix m);
	Matrix operator-(Matrix m);
	Matrix operator*(Matrix m);
	double determinant();
	Matrix inverse();
	Matrix transbose();
	Matrix operator/(Matrix m);
	Matrix dotDivision(double value);
	Matrix dotProduct(double value);
	Matrix operator-(double value);
	Matrix operator+(double value);
	Matrix dotProduct(Matrix m);
	Matrix dotDivision(Matrix m);



	//Helping functions
private:
	Matrix removeColRow(int r, int c);

};

ostream& operator<< (ostream & o, Matrix m);

#endif