#include "Parser.h"
#include <stdlib.h>
#include <fstream>
#define ROWS_SEPARATOR ";"
#define COLUMN_SEPARATOR " "


Parser::Parser()
{
	size = 0;
}


int Parser::split(string s, string separators, string** result)
{
	int numberOfElements = 1; int counter = 0; int lastPosition = 0;
	for (int i = 0; i<s.length(); i++)
	{
		for (int j = 0; j<separators.length(); j++)
		{
			if (s[i] == separators[j])
			{
				numberOfElements++;
			}
		}
	}


	*result = new string[numberOfElements];

	for (int i = 0; i<s.length(); i++)
	{
		for (int j = 0; j<separators.length(); j++)
		{
			if (s[i] == separators[j])
			{
				(*result)[counter] = s.substr(lastPosition, i - lastPosition);
				lastPosition = i + 1;
				counter++;
				while (separators.find(s[i]) != -1) i++;
			}
		}
	}
	if (lastPosition != s.length())
	{
		(*result)[counter] = s.substr(lastPosition);
	}
	else
	{
		counter--;
	}
	counter++;
	return counter;


}


int Parser::split(string s, string separators, string** result, int* numberOfSeparators, string** seps)
{
	int numberOfElements = 1; int counter = 0; int lastPosition = 0; int Separators = 0; int sepsCounter = 0;
	for (int i = 0; i<s.length(); i++)
	{
		for (int j = 0; j<separators.length(); j++)
		{
			if (s[i] == separators[j])
			{
				numberOfElements++;
				Separators++;
			}
		}
	}

	*seps = new string[Separators];
	*result = new string[numberOfElements];

	for (int i = 0; i<s.length(); i++)
	{
		for (int j = 0; j<separators.length(); j++)
		{
			if (s[i] == separators[j])
			{

				(*seps)[sepsCounter] = separators[j];
				sepsCounter++;
				(*result)[counter] = s.substr(lastPosition, i - lastPosition);
				lastPosition = i + 1;
				counter++;
			}
		}
	}
	if (lastPosition != s.length())
	{
		(*result)[counter] = s.substr(lastPosition);
	}
	else
	{
		counter--;
	}
	counter++;
	*numberOfSeparators = Separators;
	return counter;

}


string Parser::removeSidesSpaces(string s)

{
	int start = 0;
	for (int i = 0; i<s.length(); i++)
		if (s[i] == ' ')
			start++;
		else break;



		string result = s.substr(start);

		for (int i = result.length() - 1; i >= 0; i--)
			if (result[i] == ' ')
				result.erase(i, 1);
			else break;


			return result;

}

string Parser::removeAllSpaces(string s)
{
	for (int i = s.length() - 1; i >= 0; i--)
		if (s[i] == ' ')
			s.erase(i, 1);

	return s;
}


Matrix* Parser::find(string name)

{

	for (int i = 0; i<size; i++)
	{
		if (name == matrices[i]->getName())
			return matrices[i];
	}

	return NULL;
}


Matrix* Parser::add(string name, int rows, int columns)
{
	Matrix* added = new Matrix(rows, columns, name);

	matrices.push_back(added);
	size++;

	return added;
}

Matrix* Parser::findOrAdd(string name, int rows, int columns)
{
	Matrix* found = find(name);

	if (found == NULL)
		found = add(name, rows, columns);

	return found;
}


void Parser::handleLine(string line, int print)
{

	if (line.find("[") != -1) //it is declaring a new matrix
	{
		string* operation;
		split(line, "=", &operation);

		operation[0] = removeAllSpaces(operation[0]);
		operation[1] = removeSidesSpaces(operation[1]);
		operation[1].erase(operation[1].find("["), 1);
		operation[1].erase(operation[1].find("]"), 1); //remove "[,]"
		string* rows;
		int numberOfRows = split(operation[1], ROWS_SEPARATOR, &rows);
		int numberOfColumns;
		string** elementsCut= new string* [numberOfRows];


		for (int i = 0; i<numberOfRows; i++)
		{
			rows[i] = removeSidesSpaces(rows[i]);
			numberOfColumns = split(rows[i], COLUMN_SEPARATOR, &(elementsCut[i]));
		}

		Matrix* host = findOrAdd(operation[0], numberOfRows, numberOfColumns);

		for (int i = 0; i<numberOfRows; i++)
			for (int j = 0; j<numberOfColumns; j++)
			{
				elementsCut[i][j] = removeAllSpaces(elementsCut[i][j]);
				(*host)[i][j] = atof(elementsCut[i][j].c_str());
			}
		if (print == 1)
			cout << (*host);
	}



	else //it's an operation on existing matrix
	{
		
		line = removeAllSpaces(line);
		string* operation;
		split(line, "=", &operation);
		
		Matrix result = plusAndMinus(operation[1]);
		Matrix* host = findOrAdd(operation[0], result.getRows(), result.getColumns());
		(*host) = result;

		if (print == 1)
			cout << (*host);
	}


}


 void Parser::load(string filepath)
 {
 	 ifstream file1(filepath.c_str());
 	 string s;
 	while(getline(file1,s))
 	{
 		 handle(s);
 	}

 	 file1.close();
 }


void Parser::handle(string line)
{

	string* sides;
	int numberOfSides = split(line, "=", &sides);


	for (int i = numberOfSides - 1; i>1; i--)
	{
		handleLine(sides[i - 1] + string("=") + sides[i], 0);
	}

	handleLine(sides[0] + string("=") + sides[1], 1);

}



int Parser::isNumber(string s)
{
	for (int i = 0; i < s.length(); ++i)
	{
		
		if(!(  (s[i]>47 && s[i]<58) || s[i]=='.') )
			{return 0;}
	}

	return 1;
}


void Parser::inverseAndTransbose(string var)
{
	int positionInverse = var.find("inv[");
	int positionTransbose = var.find("\'");

	if(positionInverse != -1)
	{
		string original = var;
			if(positionTransbose == (var.length()-1))
				original.erase(var.length()-1,1);
		original.erase(0,4);

		original.erase(original.find("]"),1);

		if(original.find("\'")!=-1)
		{
			string nonInversed = original;
		nonInversed.erase(nonInversed.length()-1,1);

		Matrix nonInversedM = *find(nonInversed);
		Matrix* added = findOrAdd(original,nonInversedM.getColumns(),nonInversedM.getRows());
		*added = nonInversedM.transbose();
		}


		Matrix originalM = *find(original);
		string onlyInverse = var;

		if(positionTransbose == (var.length()-1))
				onlyInverse.erase(var.length()-1,1);


		Matrix* added = findOrAdd(onlyInverse,originalM.getColumns(),originalM.getRows());
		*added = originalM.inverse();



	}


	if(positionTransbose == (var.length()-1))
	{
		string original = var;
		original.erase(original.length()-1,1);

		Matrix originalM = *find(original);
		Matrix* added = findOrAdd(var,originalM.getColumns(),originalM.getRows());
		*added = originalM.transbose();
	}
}



Matrix Parser::plusAndMinus(string line)
{
	 while(1)
			 {
			 	int pos = line.find("./");
			 	if(pos==-1) break;
			 	line.replace(pos,2,"$");
			 }

			while(1)
			 {
			 	int pos = line.find(".*");
			 	if(pos==-1) break;
			 	line.replace(pos,2,"#");
			 }

			 while(1)
			 {
			 	int pos = line.find("inv("); int posRight;
			 	if(pos==-1) break;
			 	line.replace(pos,4,"inv[");
			 	posRight = line.find(")",pos);
			 	line.replace(posRight,1,"]");

			 }


 
		
		Matrix result;

		string* seps;
		int numberOfSeparators;
		string* variables;
		int numberOfVariables;

		numberOfVariables = split(line, "+-", &variables, &numberOfSeparators, &seps);

		if(isNumber(variables[0])) // setting result to first variable
		{
			for(int i=0; i<numberOfVariables; i++)
				if(!isNumber(variables[i]))
				{
					Matrix first = mulAndDivide(variables[i]);
					result.setRows(first.getRows());
					result.setColumns(first.getColumns());

					double val = atof(variables[0].c_str());
					result.initialize(val);
					break;
				}
		}

		else( result = mulAndDivide(variables[0]));

			// if(result.getRows()==0 && result.getColumns()==0) 
			// 			{
			// 				result.setRows(1);
			// 				result.setColumns(1);
			// 				double val = atof(variables[0].c_str());
			// 				result.initialize(val);
			// 			}


		for (int i = 0; i<numberOfSeparators; i++)
		{
			if (!seps[i].compare("+"))
			{
				if(isNumber(variables[i+1]))
			 			{
			 				double val = atof(variables[i+1].c_str());
			 				result = result + val;
			 			}
			 	else
				
					result = result + mulAndDivide(variables[i+1]);
			}
			
			else if (!seps[i].compare("-"))
			
			{
				if(isNumber(variables[i+1]))
			 			{
			 				double val = atof(variables[i+1].c_str());
			 				result = result - val;
			 			}
			 	else
				
					result = result - mulAndDivide(variables[i+1]);
			}


			
			 
		}
		return result;
	}




Matrix Parser::mulAndDivide(string line)
{
	Matrix result;
		string* seps;
		int numberOfSeparators;
		string* variables;
		int numberOfVariables;

		numberOfVariables = split(line, "/*$#", &variables, &numberOfSeparators, &seps);

		for(int i=0; i<numberOfVariables; i++)
			inverseAndTransbose(variables[i]);

		if(isNumber(variables[0])) // setting result to first variable
		{
			for(int i=0; i<numberOfVariables; i++)
				if(!isNumber(variables[i]))
				{
					Matrix first = *find(variables[i]);
					result.setRows(first.getRows());
					result.setColumns(first.getColumns());

					double val = atof(variables[0].c_str());
					result.initialize(val);
					break;
				}
		}

		else 
			{
				result = *find(variables[0]);
			}


			// if(result.getRows()==0 && result.getColumns()==0) 
			// {
			// 	result.setRows(1);
			// 	result.setColumns(1);
			// 	double val = atof(variables[0].c_str());
			// 	result.initialize(val);
			// }

			for (int i = 0; i<numberOfSeparators; i++)
		{
			
			
			if (!seps[i].compare("*"))
				result = result * (*(find(variables[i + 1])));


			else if (!seps[i].compare("/"))
				result = result / (*find(variables[i + 1]));


			 else if(!seps[i].compare("$"))
			 		{
			 			if(isNumber(variables[i+1]))
			 			{
			 				double val = atof(variables[i+1].c_str());
			 				result = result.dotDivision(val);
			 			}

						else

			 				result = result.dotDivision(*find(variables[i + 1]));

			 		}

			 else if(!seps[i].compare("#"))
			 		{
						if(isNumber(variables[i+1]))
					 			{
					 				double val = atof(variables[i+1].c_str());
					 				result = result.dotProduct(val);
					 			}
					 		
					 	else

			 				result = result.dotProduct(*find(variables[i + 1]));

			 		}
			 
		}


		return result;
		
	}



