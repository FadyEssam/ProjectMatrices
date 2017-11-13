#ifndef MATRIXHH
#define MATRIXHH
#include<iostream>
#include<string>
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
	// Matrix (const Matrix &m);
	// ~Matrix();
	Matrix(int r, int c);
	Matrix(int r, int c, string n);
	void initialize(double value);
	void destroy();
	void setRows(int r);
	void setColumns(int c);
	void setName(string s);
	int getColumns();
	int getRows();
	string getName();
	void setConstant(double value);
	double getConstant() const;
	int isConstant() const;
	//printing
	void print();


	//changing values
	void setElement(int r, int c, double value);
	double* operator[](int r) const;
	

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
	Matrix dotPower(Matrix m);
	Matrix dotPower(double value);
	Matrix msqrt();
	Matrix msin();
	Matrix mcos();
	Matrix mtan();



	//Helping functions
private:
	Matrix removeColRow(int r, int c);

};

ostream& operator<< (ostream & o, Matrix m);
 Matrix zeros(int r, int c);
 Matrix ones(int r, int c);
 Matrix rand(int r, int c);
 Matrix eye(int r, int c);
#endif