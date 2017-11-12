#include "Matrix.h"
#include <iostream>
#include <ostream>
#define DEFAULT_NAME "ans"
#define MAX_RANDOM 100


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

// Matrix::Matrix (const Matrix &m)
// {
// 	if(m.isConstant())
// 	{
// 		this->setConstant(m.getConstant());
// 		name = m.name;
// 		return;
// 	}

	
// 	rows = m.rows;
// 	columns = m.columns;
// 	name = m.name;
// 	elements = new double*[rows];
// 	for (int i = 0; i<rows; i++)
// 		elements[i] = new double[columns];


// 	for (int i = 0; i<rows; i++)
// 		for (int j = 0; j<columns; j++)
// 			elements[i][j] = m[i][j];
// }


// Matrix::~Matrix()
// {
// 	 //this->destroy();
// }


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


int Matrix::getColumns()
{
	return columns;
}

int Matrix::getRows()
{
	return rows;
}


string Matrix::getName()
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
Matrix Matrix::operator+ (Matrix m)
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


	if ((m.rows != rows) || (m.columns != columns)) throw "You can't add two matrices with different R,C";

	else
	{
		Matrix result(rows, columns);

		for (int i = 0; i<rows; i++)
			for (int j = 0; j<columns; j++)
				result[i][j] = elements[i][j] + m[i][j];

		return result;

	}
}

Matrix Matrix::operator- (Matrix m)
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


	if ((m.rows != rows) || (m.columns != columns)) throw "You can't substract two matrices with different R,C";

	else
	{
		Matrix result(rows, columns);

		for (int i = 0; i<rows; i++)
			for (int j = 0; j<columns; j++)
				result[i][j] = elements[i][j] - m[i][j];

		return result;

	}
}


void Matrix::operator= (Matrix m) // to make it separately editable
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



Matrix Matrix::operator* (Matrix m) // to make it separately editable
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

	if (columns != m.rows)  throw "Functions can't be multiplied";

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


Matrix Matrix::dotProduct (Matrix m)
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


	if ((m.rows != rows) || (m.columns != columns)) throw "You can't add two matrices with different R,C";

	else
	{
		Matrix result(rows, columns);

		for (int i = 0; i<rows; i++)
			for (int j = 0; j<columns; j++)
				result[i][j] = elements[i][j] * m[i][j];

		return result;

	}
}


Matrix Matrix::dotDivision (Matrix m)
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

	if ((m.rows != rows) || (m.columns != columns)) throw "You can't add two matrices with different R,C";

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


Matrix Matrix::operator/ (Matrix m) // to make it separately editable
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

	Matrix tempM(rows, columns);


	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
			tempM[i][j] = elements[i][j];

	return tempM*(m.inverse());



}


double Matrix::determinant()
{
	double result = 0; char sign;

	if (rows != columns) throw "Can't compute diterminant for this function";

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


Matrix Matrix::removeColRow(int r, int c)
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





Matrix Matrix::transbose()
{

	Matrix result(columns, rows);

	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
		{
			result[j][i] = elements[i][j];
		}
	return result;
}




Matrix Matrix::inverse()

{
	if (rows != columns) throw "Can't compute inverse for this function";

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


Matrix Matrix::operator^ (double value)
{

	if(value==0) return *(this);
	
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


Matrix Matrix::operator^ (Matrix m)
{
	if(!m.isConstant())
	{
		throw "you can't have power of matrix";
	}

	else
	{
		return *(this) ^ m.getConstant();
	}
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
	if( (rows == 0) && (columns == 0) && (elements != NULL))
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
			result[i][j] = random()%MAX_RANDOM+1;
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