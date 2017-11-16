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
	Matrix (const Matrix &m);
	~Matrix();
	Matrix(int r, int c);
	Matrix(int r, int c, string n);
	void initialize(double value);
	void destroy();
	void setRows(int r);
	void setColumns(int c);
	void setName(string s);
	int getColumns() const;
	int getRows() const;
	string getName() const;
	void setConstant(double value);
	double getConstant() const;
	int isConstant() const;
	//printing
	void print();


	//changing values
	void setElement(int r, int c, double value);
	double* operator[](int r) const;
	void stickToSide(const Matrix & m);
	void stickToBottom(const Matrix & m);
	

	//Arithmatics
	Matrix operator^(const Matrix & m);
	Matrix operator^(double value);
	Matrix operator+(const Matrix & m);
	void operator=(const Matrix & m);
	Matrix operator-(const Matrix & m);
	Matrix operator*(const Matrix & m);
	double determinant() const;
	Matrix inverse() const;
	Matrix transbose() const;
	Matrix operator/(const Matrix & m);
	Matrix dotDivision(double value);
	Matrix dotProduct(double value);
	Matrix operator-(double value);
	Matrix operator+(double value);
	Matrix dotProduct(const Matrix & m);
	Matrix dotDivision(const Matrix & m);
	Matrix dotPower(const Matrix & m);
	Matrix dotPower(double value);
	Matrix powerFraction(double value);
	Matrix msqrt();
	Matrix msin();
	Matrix mcos();
	Matrix mtan();
	int isZeroMatrix() const;
	double advancedDeterminant() const;




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