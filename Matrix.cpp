#include "Matrix.h"
#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <cmath>
#define DEFAULT_NAME "ans"
#define MAX_RANDOM 100
#define TAN(x) (sin(x)/cos(x))



Matrix::Matrix()
{
	rows = 0;
	columns = 0;
	elements = NULL;
	name = DEFAULT_NAME;
}


Matrix::Matrix(int r, int c)
{
	rows = r;
	columns = c;
	name = DEFAULT_NAME;
	elements = new double*[rows];
	for (int i = 0; i<rows; i++)
		elements[i] = new double[columns];

}


Matrix::Matrix(int r, int c, string n)
{
	rows = r;
	columns = c;
	name = n;
	elements = new double*[rows];
	for (int i = 0; i<rows; i++)
		elements[i] = new double[columns];


}

void Matrix::initialize(double value)
{
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
			elements[i][j] = value;
}

Matrix::Matrix (const Matrix &m)
{
	if(m.isConstant())
	{
		rows = 0;
		columns = 0;
		elements = new double*;
		elements[0] = new double;
		elements[0][0] = m.getConstant();
		name = m.name;
		return;
	}

	
	rows = m.rows;
	columns = m.columns;
	name = m.name;
	elements = new double*[rows];
	for (int i = 0; i<rows; i++)
		elements[i] = new double[columns];


	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
			elements[i][j] = m[i][j];
}


Matrix::~Matrix()
{
	 this->destroy();
}


void Matrix::destroy()
{
	if(elements != NULL)
	
	{
		for (int i = 0; i<rows; i++)
		delete[] elements[i];

		delete[] elements;
	}
	rows = 0;
	columns = 0;
	elements = NULL;

}

void Matrix::setRows(int r)
{
	this->destroy();
	rows = r;
	elements = new double*[rows];

}

void Matrix::setColumns(int c)
{
	columns = c;
	for (int i = 0; i<rows; i++)
		elements[i] = new double[columns];
}

void Matrix::setName(string s)
{

	name = s;
}


int Matrix::getColumns() const
{
	return columns;
}

int Matrix::getRows() const
{
	return rows;
}


string Matrix::getName() const
{
	return name;
}

//================================== Printing


void Matrix::print()
{
	cout<<endl<<name<<"="<<endl;

	if(isConstant())
	{
		cout<<"\t"<<getConstant()<<endl<<endl;
	}


	for (int i = 0; i<rows; i++)
	{
		cout<<"\t";
		for (int j = 0; j<columns; j++)
		{
			cout << elements[i][j] << "\t";

		}
		cout << "\n";
	}
	cout << endl;
}


ostream& operator<< (ostream & o, Matrix m)
{
	m.print();
	return o;
}

//================================== Editing

void Matrix::setElement(int r, int c, double value)
{
	elements[r][c] = value;
}

double* Matrix::operator[](int r) const
{
	return elements[r];
}


//======================================== Arihtmatic
Matrix Matrix::operator+ (const Matrix & m)
{

	if(m.isConstant())
	{
		return *(this)+m.getConstant();
	}


	if(isConstant())
	{

		if(m.isConstant())
		{
			return *(this)+m.getConstant();
		}

		Matrix result(m.getRows(),m.getColumns());
		result.initialize(elements[0][0]);
		return result+m;
	}


	if ((m.rows != rows) || (m.columns != columns)) throw "You can't add two matrices with different rows or columns";

	else
	{
		Matrix result(rows, columns);

		for (int i = 0; i<rows; i++)
			for (int j = 0; j<columns; j++)
				result[i][j] = elements[i][j] + m[i][j];

		return result;

	}
}

Matrix Matrix::operator- (const Matrix & m)
{

	if(m.isConstant())
	{
		return *(this)-m.getConstant();
	}


	if(isConstant())
	{
		if(m.isConstant())
		{
			return *(this)-m.getConstant();
		}
		Matrix result(m.getRows(),m.getColumns());
		result.initialize(elements[0][0]);
		return result-m;
	}


	if ((m.rows != rows) || (m.columns != columns)) throw "You can't substract two matrices with different rows or columns";

	else
	{
		Matrix result(rows, columns);

		for (int i = 0; i<rows; i++)
			for (int j = 0; j<columns; j++)
				result[i][j] = elements[i][j] - m[i][j];

		return result;

	}
}


void Matrix::operator= (const Matrix & m) // to make it separately editable
{


	

	if(m.isConstant())
	{
		this->setConstant(m.getConstant());
		return;
	}

	if (this->elements != NULL)this->destroy();
	
	rows = m.rows;
	columns = m.columns;

	elements = new double*[rows];
	for (int i = 0; i<rows; i++)
		elements[i] = new double[columns];


	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
			elements[i][j] = m[i][j];



}



Matrix Matrix::operator* (const Matrix & m) // to make it separately editable
{

	if(m.isConstant())
	{
		return this->dotProduct(m.getConstant());
	}


	if(isConstant())
	{

		if(m.isConstant())
		{
			return this->dotProduct(m.getConstant());
		}

		Matrix result(m.getRows(),m.getColumns());
		result.initialize(elements[0][0]);
		return result.dotProduct(m);
	}

	if (columns != m.rows)  throw "The two matrices can't be multiplied";

	else
	{
		Matrix result(rows, m.columns);

		for (int i = 0; i<rows; i++)
			for (int j = 0; j<m.columns; j++)
			{
				result[i][j] = 0;
				for (int k = 0; k<columns; k++)
				{
					result[i][j] += (elements[i][k] * m[k][j]);
				}

			}

		return result;

	}



}


Matrix Matrix::dotProduct (const Matrix & m)
{

	if(m.isConstant())
	{
		return this->dotProduct(m.getConstant());
	}


	if(isConstant())
	{
			if(m.isConstant())
		{
			return this->dotProduct(m.getConstant());
		}

		Matrix result(m.getRows(),m.getColumns());
		result.initialize(elements[0][0]);
		return result.dotProduct(m);
	}


	if ((m.rows != rows) || (m.columns != columns)) throw "The two matrices can't be multiplied";

	else
	{
		Matrix result(rows, columns);

		for (int i = 0; i<rows; i++)
			for (int j = 0; j<columns; j++)
				result[i][j] = elements[i][j] * m[i][j];

		return result;

	}
}


Matrix Matrix::dotDivision (const Matrix & m)
{
	if(m.isConstant())
	{
		return this->dotDivision(m.getConstant());
	}


	if(isConstant())
	{
		if(m.isConstant())
		{
			return this->dotDivision(m.getConstant());
		}

		Matrix result(m.getRows(),m.getColumns());
		result.initialize(elements[0][0]);
		return result.dotDivision(m);
	}

	if ((m.rows != rows) || (m.columns != columns)) throw "The two matrices can't be divided";

	else
	{
		Matrix result(rows, columns);

		for (int i = 0; i<rows; i++)
			for (int j = 0; j<columns; j++)
				result[i][j] = elements[i][j] / m[i][j];

		return result;

	}
}

Matrix Matrix::dotProduct(double value)
{

	if(isConstant())
	{
		Matrix result = *(this);
		result.elements[0][0] *= value;
		return result;
	}

	Matrix result(rows,columns);

	
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
			result[i][j] = elements[i][j] * value;


	return result;
}



Matrix Matrix::dotDivision(double value)
{
	if(isConstant())
	{
		Matrix result = *(this);
		result.elements[0][0] /= value;
		return result;
	}

	Matrix result(rows,columns);

	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
			result[i][j] = elements[i][j] / value;

	return result;
}


Matrix Matrix::operator-(double value)
{

	if(isConstant())
	{
		Matrix result = *(this);
		result.elements[0][0] -= value;
		return result;
	}

	Matrix result(rows,columns);


	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
			result[i][j] = elements[i][j] - value;


	return result;
}



Matrix Matrix::operator+(double value)
{
	if(isConstant())
	{
		Matrix result = *(this);
		result.elements[0][0] += value;
		return result;
	}

	Matrix result(rows,columns);

		
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
			result[i][j] = elements[i][j] + value;

	return result;
}


Matrix Matrix::operator/ (const Matrix & m) // to make it separately editable
{
	if(m.isConstant())
	{
		return this->dotDivision(m.getConstant());
	}


	if(isConstant())
	{
		if(m.isConstant())
		{
			return this->dotDivision(m.getConstant());
		}

		Matrix result(m.getRows(),m.getColumns());
		result.initialize(elements[0][0]);
		return result.dotDivision(m);
	}

	if (columns != m.rows)  throw "The two matrices can't be divided";
	Matrix tempM(rows, columns);


	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
			tempM[i][j] = elements[i][j];

	return tempM*(m.inverse());



}


double Matrix::determinant() const
{
	double result = 0; char sign;

	if (rows != columns) throw "The matrix must be square to calculate it's diterminant";

	else
	{
		if (rows == 2)
			return ((elements[0][0] * elements[1][1]) - (elements[0][1] * elements[1][0]));

		else
		{
			for (int i = 0; i<columns; i++)

			{
				if (i % 2 == 0)
					sign = 1;
				else sign = -1;


				result += sign* elements[0][i] * (this->removeColRow(0, i).determinant());
			}
			return result;
		}


	}

}


Matrix Matrix::removeColRow(int r, int c) const
{

	Matrix result(rows - 1, columns - 1);
	int i2 = 0; int j2 = 0;

	for (int i = 0; i<rows - 1; i++, i2++)
	{
		for (int j = 0; j < columns - 1; j++, j2++)
		{
			if (i2 == r) i2++;
			if (j2 == c) j2++;

			result[i][j] = elements[i2][j2];
		}
		j2 = 0;
	}
	return result;
}





Matrix Matrix::transbose() const
{

	Matrix result(columns, rows);

	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
		{
			result[j][i] = elements[i][j];
		}
	return result;
}




Matrix Matrix::inverse() const

{
	if (rows != columns) throw "The matrix must be square to calculate inverse";

	Matrix tempM(rows, columns); int sign;  double temp;


	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
			tempM[i][j] = elements[i][j];

	double determinant = this->determinant();

	if (rows == 2)
	{

		tempM[0][0] = elements[1][1] / determinant;
		tempM[1][1] = elements[0][0] / determinant;
		tempM[0][1] = (-1 * elements[0][1]) / determinant;
		tempM[1][0] = (-1 * elements[1][0]) / determinant;

		return tempM;
	}

	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
		{
			temp = this->removeColRow(i, j).determinant();
			temp = temp / determinant;

			if ((i % 2) == (j % 2)) sign = 1;
			else sign = -1;

			temp = temp*sign;
			tempM[i][j] = temp;


		}


	return tempM.transbose();


}


Matrix Matrix::dotPower (double value)
{

	
	if(isConstant())
	{
		Matrix result;
		result = *(this);
		result[0][0] = pow(result[0][0],value);
		return result; 
	}

	else
	{
		Matrix result(rows,columns);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				result[i][j] = pow(elements[i][j],value);
			}
		}

		return result;
	}

} 


Matrix Matrix::operator^(double value)
{
	
	
	if(isConstant())
	{
		Matrix result;
		result = *(this);
		result[0][0] = pow(result[0][0],value);
		return result; 
	}



	else
	{
		value = round(value);
			if(rows!=columns) throw "can't power non-square matrix";
		Matrix result;
		result.setConstant(1);

			if(value<0)
			{
				value = -1*value;
				return eye(rows,columns)/((*(this))^value);
			}
		else
		{

			for (int i = 0; i < value; ++i)
			{
				result = result*(*this);
			}

			return result;
		}
	}

} 


Matrix Matrix::operator^ (const Matrix & m)
{
	if(!m.isConstant())
	{
		throw "you can't have power of matrix";
	}

	else
	{
		return (*(this))^(m.getConstant());
	}
}

Matrix Matrix::dotPower (const Matrix & m)
{
	if(!m.isConstant())
	{
		throw "you can't have power of matrix";
	}

	else
	{
		return (*(this)).dotPower(m.getConstant());
	}
}


Matrix Matrix::msqrt()
{
	if(isConstant())
	{
		Matrix result;
		result.setConstant( sqrt(this->getConstant()) );
		return result;
	}


	Matrix result(rows,columns);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			result[i][j] = pow(elements[i][j],0.5);
		}
	}

	return result;
}


Matrix Matrix::msin()
{
	if(isConstant())
	{
		Matrix result;
		result.setConstant( sin(this->getConstant()) );
		return result;
	}


	Matrix result(rows,columns);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			result[i][j] = sin(elements[i][j]);
		}
	}

	return result;
}



Matrix Matrix::mcos()
{
	if(isConstant())
	{
		Matrix result;
		result.setConstant( cos(this->getConstant()) );
		return result;
	}


	Matrix result(rows,columns);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			result[i][j] = cos(elements[i][j]);
		}
	}

	return result;
}




Matrix Matrix::mtan()
{
	if(isConstant())
	{
		Matrix result; double val = this->getConstant();
		result.setConstant( TAN(val));
		return result;
	}


	Matrix result(rows,columns);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			result[i][j] = TAN(elements[i][j]);
		}
	}

	return result;
}

// constants section=================

void Matrix::setConstant(double value)
{
	this->destroy();
	elements = new double*;
	elements[0] = new double;
	elements[0][0] = value;
}

double Matrix::getConstant() const
	{
		return elements[0][0];
	}
	

int Matrix::isConstant() const
{
	if( ((rows == 0) && (columns == 0) && (elements != NULL) )|| ((rows==1) && (columns==1)) )
		return 1;

	else 
		return 0;
}


//============================================

//Special matrices ===================================

Matrix zeros(int r, int c)
{
	Matrix result(r,c);
	result.initialize(0);
	return result;
}



Matrix ones(int r, int c)
{
	Matrix result(r,c);
	result.initialize(1);
	return result;
}

Matrix rand(int r, int c)
{
	Matrix result(r,c);

	for (int i = 0; i < r; ++i)
	{
		for(int j=0; j<c; j++)
		{
			result[i][j] = rand()%MAX_RANDOM+1;
		}
	}


	return result;
}



Matrix eye(int r, int c)
{
	Matrix result(r,c);

	for (int i = 0; i < r; ++i)
	{
		for(int j=0; j< c; j++)
		{

			result[i][j] = (i==j)?1:0;
		}
	}


	return result;
}

//====================================================

//subMatrix===========================================

void Matrix::stickToSide(const Matrix & m)
{
	if(rows==0 && columns==0 && elements==NULL)
	{
		(*this) = m;
		return;
	}




	if(isConstant())
	{

			if(m.isConstant())
			{

				Matrix result(1,2);
				result[0][0] = elements[0][0];
				result[0][1] = m.getConstant();

				(*this) = result;
				return;
			}




					else
			{
				if(m.rows!=1) throw "invalid dimensions";

				Matrix result(1,1+m.columns);

				result[0][0] = elements[0][0];
				for (int i = 1; i < m.columns+1; ++i)
				{
					result[0][i] = m[0][i-1];
				}

				(*this) = result;
				return;
			}
	}



	if(m.isConstant())
	{
		if(rows!=1) throw "invalid dimensions";

		Matrix result(rows,columns+1);
		for (int i = 0; i <columns; i++)
		{
			result[0][i] = elements[0][i];
		}

		result[0][columns] = m.getConstant();
		(*this) = result;
		return;
	}



	else
	{
		if(rows != m.rows) throw "invalid dimensions";

		Matrix result(rows,columns+m.columns);

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns+m.columns; ++j)
			{
				if(j<columns)
					result[i][j] = elements[i][j];
				else
					result[i][j] =  m[i][j-columns];
			}
		}

		(*this) = result;
		return;
	}



}


void Matrix::stickToBottom(const Matrix & m)
{
	if(rows==0 && columns==0 && elements==NULL)
	{
		(*this) = m;
		return;
	}

	if(isConstant())
	{

			if(m.isConstant())
			{

				Matrix result(2,1);
				result[0][0] = elements[0][0];
				result[1][0] = m.getConstant();

				(*this) = result;
				return;
			}




					else
			{
				if(m.columns!=1) throw "invalid dimensions";

				Matrix result(1+m.rows,1);

				result[0][0] = elements[0][0];
				for (int i = 1; i < m.rows+1; ++i)
				{
					result[i][0] = m[i-1][0];
				}

				(*this) = result;
				return;
			}
	}



	if(m.isConstant())
	{
		if(columns!=1) throw "invalid dimensions";

		Matrix result(rows+1,columns);
		for (int i = 0; i <rows; i++)
		{
			result[i][0] = elements[i][0];
		}

		result[rows][0] = m.getConstant();
		(*this) = result;
		return;
	}



	else
	{
		if(columns != m.columns) throw "invalid dimensions";

		Matrix result(rows+m.rows,columns);

		for (int i = 0; i < rows+m.rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				if(i<rows)
					result[i][j] = elements[i][j];
				else
					result[i][j] =  m[i-rows][j];
			}
		}

		(*this) = result;
		return;
	}



}
//====================================================