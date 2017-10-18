#ifndef MATRIXHH
#define MATRIXHH
#include<iostream>
using namespace std;

class Matrix
{
private:
	int rows,columns;
	double** elements;

public:
//essential
	Matrix();
	Matrix(int r, int c);
	//void Matrix(Matrix& m);
	void destroy();
	void setRows(int r);
	void setColumns(int c);
	int getColumns();
	int getRows();

//printing
	void print();
	

//changing values
	void setElement(int r, int c, double value);
	double* operator[](int r);


//Arithmatics

	Matrix operator+(Matrix m);
	void operator=(Matrix m);
	Matrix operator-(Matrix m);
	Matrix operator*(Matrix m);
	double determinant();
	Matrix inverse();
	Matrix transbose();
	Matrix operator/(Matrix m);

	

//Helping functions
private:
	Matrix removeColRow(int r, int c);

};

 ostream& operator<< (ostream & o, Matrix m);


#endif