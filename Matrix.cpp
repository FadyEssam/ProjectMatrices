#include "Matrix.h"
#include <iostream>
#include <ostream>
#define DEFAULT_NAME ""


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
	elements = new double* [rows];
	for(int i=0; i<rows; i++)
		elements[i]  =  new double[columns];
}


// void Matrix::Matrix(Matrix& m)
// {
// 	rows = m.getRows();
// 	columns = m.getColumns();

// 	elements = new double* [rows];
// 	for(int i=0; i<rows; i++)
// 		elements[i]  =  new double[columns];

// 	for(int i=0; i<rows; i++)
// 			for(int j=0; j<columns; j++)
// 				elements[i][j] = m[i][j];

// }


void Matrix::destroy()
{

	for(int i=0; i<rows; i++)
		delete[] elements[i];

	delete[] elements;
	rows = 0;
	columns = 0;

}

void Matrix::setRows(int r)
{
	rows = r;
}

void Matrix::setColumns(int c)
{
	columns = c;
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
	for(int i=0; i<rows; i++)
		{
			for(int j=0; j<columns; j++)
		{
			cout<<elements[i][j]<<"\t";

		}
		cout<<"\n";
	}
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

	double* Matrix::operator[](int r)
	{
		return elements[r];
	}


//======================================== Arihtmatic
Matrix Matrix::operator+ (Matrix m)
{
	if((m.rows!= rows) || (m.columns != columns)) throw "You can't add two matrices with different R,C";

	else
	{
		Matrix result(rows,columns);

		for(int i=0; i<rows; i++)
			for(int j=0; j<columns; j++)
				result[i][j] = elements[i][j] + m[i][j];

		return result;

	}
}

Matrix Matrix::operator- (Matrix m)
{
	if((m.rows!= rows) || (m.columns != columns)) throw "You can't substract two matrices with different R,C";

	else
	{
		Matrix result(rows,columns);

		for(int i=0; i<rows; i++)
			for(int j=0; j<columns; j++)
				result[i][j] = elements[i][j] - m[i][j];

		return result;

	}
}


void Matrix::operator= (Matrix m) // to make it separately editable
{


		if(this->elements!=NULL)this->destroy();
		rows = m.rows;
		columns = m.columns;

		elements = new double* [rows];
	for(int i=0; i<rows; i++)
 		elements[i]  =  new double[columns];


		for(int i=0; i<rows; i++)
			for(int j=0; j<columns; j++)
				elements[i][j] =m[i][j];



}



Matrix Matrix::operator* (Matrix m) // to make it separately editable
{

		if(columns!= m.rows)  throw "Functions can't be multiplied";

		else
		{
			Matrix result(rows,m.columns);

			for(int i=0; i<rows; i++)
				for(int j=0; j<m.columns; j++)
				{
					result[i][j]  = 0;
					for(int k=0; k<columns; k++)
					{
						result[i][j] += (elements[i][k]  * m[k][j]);
					}

				}

			return result;

		}



}

Matrix Matrix::operator/ (Matrix m) // to make it separately editable
{
	Matrix tempM(rows,columns);


		for(int i=0; i<rows; i++)
			for(int j=0; j<columns; j++)
				tempM[i][j] = elements[i][j];

	return tempM*(m.inverse());



}


double Matrix::determinant()
{
	double result=0; char sign;

	if(rows!=columns) throw "Can't compute diterminant for this function";

	else
	{
		if(rows == 2)
			return ((elements[0][0] * elements[1][1]) -  (elements[0][1] * elements[1][0]));

		else
		{
			for(int i=0; i<columns; i++)

				{
					if(i%2==0)
						sign = 1;
					else sign = -1;


					result += sign* elements[0][i] * (this->removeColRow(0,i).determinant());
				}
				return result;
		}


	}

}


	Matrix Matrix::removeColRow(int r, int c)
	{

		Matrix result(rows-1,columns-1);
		int i2=0; int j2=0;

		for(int i=0; i<rows-1; i++,i2++)
		{
			for (int j = 0; j < columns-1; j++,j2++)
			{
				if(i2==r) i2++;
				if(j2==c) j2++;

				result[i][j] = elements[i2][j2];
			}
			j2=0;
		}
			return result;
	}





Matrix Matrix::transbose()
{

	Matrix result (columns,rows);

	for(int i=0; i<rows; i++)
			for(int j=0; j<columns; j++)
			{
				result[j][i] = elements[i][j];
			}
return result;
}




	Matrix Matrix::inverse()

	{
			if(rows!=columns) throw "Can't compute inverse for this function";

		Matrix tempM(rows,columns); int sign;  double temp;


		for(int i=0; i<rows; i++)
			for(int j=0; j<columns; j++)
				tempM[i][j] = elements[i][j];

		double determinant = this->determinant();

		if(rows==2)
		{

			tempM[0][0] = elements[1][1]/determinant;
			tempM[1][1] = elements[0][0]/determinant;
			tempM[0][1] = (-1 * elements[0][1])/determinant;
			tempM[1][0] = (-1 * elements[1][0])/determinant;

			return tempM;
		}

		for(int i=0; i<rows; i++)
			for(int j=0; j<columns; j++)
			{
				temp = this->removeColRow(i,j).determinant();
				temp = temp/determinant;

				if((i%2) == (j%2)) sign = 1;
				else sign = -1;

				temp = temp*sign;
				tempM[i][j] = temp;


			}


			return tempM.transbose();


	}
