#include "Parser.h"
#include <stdlib.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#define ROWS_SEPARATOR ";"
#define COLUMN_SEPARATOR " "
#define FAKE_NAME "temporaryFakeForParenthese"

Parser::Parser()
{
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
		if(s[i]=='[') //skip till ']'
		{
			i = s.find(']',i);
		}


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
		if (s[i] == ' ' || s[i]== '\t')
			start++;
		else break;



		string result = s.substr(start);

		for (int i = result.length() - 1; i >= 0; i--)
			if (result[i] == ' ' || result[i] == '\t')
				result.erase(i, 1);
			else break;


			return result;

}

string Parser::removeAllSpaces(string s)
{
	for (int i = s.length() - 1; i >= 0; i--)
		if (s[i] == ' ' || s[i]=='\t')
			s.erase(i, 1);

	return s;
}


Matrix* Parser::find(string name)

{

	for (int i = 0; i<matrices.size(); i++)
	{
		if (name == matrices[i]->getName())
			return matrices[i];
	}

int eyesPlace = name.find("eye[");

if( eyesPlace == 0)
{
	string s = name.substr(4);
	string first = s.substr(0,s.find(","));
	string second = s.substr(s.find(",")+1);
	removeAllSpaces(first);
	removeAllSpaces(second);
	int r = atoi(first.c_str());
	int c = atoi(second.c_str());

	Matrix* added = new Matrix;
	*added = eye(r,c);
	added->setName(name);
	matrices.push_back(added);
	return added;

}



int zerosPlace = name.find("zeros[");

if( zerosPlace == 0)
{
	string s = name.substr(6);
	string first = s.substr(0,s.find(","));
	string second = s.substr(s.find(",")+1);
	removeAllSpaces(first);
	removeAllSpaces(second);
	int r = atoi(first.c_str());
	int c = atoi(second.c_str());

	Matrix* added = new Matrix;
	*added = zeros(r,c);
	added->setName(name);
	matrices.push_back(added);
	return added;

}



int onesPlace = name.find("ones[");

if( onesPlace == 0)
{
	string s = name.substr(5);
	string first = s.substr(0,s.find(","));
	string second = s.substr(s.find(",")+1);
	removeAllSpaces(first);
	removeAllSpaces(second);
	int r = atoi(first.c_str());
	int c = atoi(second.c_str());

	Matrix* added = new Matrix;
	*added = ones(r,c);
	added->setName(name);
	matrices.push_back(added);
	return added;

}


int randPlace = name.find("rand[");

if( randPlace == 0)
{
	string s = name.substr(5);
	string first = s.substr(0,s.find(","));
	string second = s.substr(s.find(",")+1);
	removeAllSpaces(first);
	removeAllSpaces(second);
	int r = atoi(first.c_str());
	int c = atoi(second.c_str());

	Matrix* added = new Matrix;
	*added = rand(r,c);
	added->setName(name);
	matrices.push_back(added);
	return added;

}



	return NULL;
}




Matrix* Parser::add(string name, int rows, int columns)
{
	Matrix* added = new Matrix(rows, columns, name);

	matrices.push_back(added);

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

		if(operation[1][operation[1].length()-1]==';')
		operation[1].erase(operation[1].length()-1,1);

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
		host->setRows(numberOfRows);
		host->setColumns(numberOfColumns);
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

		//replacing==================
		while(1)
			 {
			 	int pos = operation[1].find("./");
			 	if(pos==-1) break;
			 	operation[1].replace(pos,2,"$");
			 }


			 while(1)
			 {
			 	int pos = operation[1].find(".^");
			 	if(pos==-1) break;
			 	operation[1].replace(pos,2,"%");
			 }

		while(1)
			 {
			 	int pos = operation[1].find(".+");
			 	if(pos==-1) break;
			 	operation[1].replace(pos,2,"+");
			 }


			 while(1)
			 {
			 	int pos = operation[1].find(".-");
			 	if(pos==-1) break;
			 	operation[1].replace(pos,2,"-");
			 }

			while(1)
			 {
			 	int pos = operation[1].find(".*");
			 	if(pos==-1) break;
			 	operation[1].replace(pos,2,"#");
			 }

			 while(1)
			 {
			 	int pos = operation[1].find("inv("); int posRight;
			 	if(pos==-1) break;
			 	operation[1].replace(pos,4,"inv[");
			 	int parentheses = 1;
			 	for (int i = pos+1; i < operation[1].length(); ++i)
			 	{
			 		if(operation[1][i] == '(')
			 			parentheses++;
			 		if(operation[1][i] == ')')
			 			parentheses--;

			 		if(parentheses==0)
			 		{
			 			pos = i;
			 			break;
			 		}
			 	}

			 	
			 	operation[1].replace(pos,1,"]");

			 }


			while(1)
			 {
			 	int pos = operation[1].find("eye("); int posRight;
			 	if(pos==-1) break;
			 	operation[1].replace(pos,4,"eye[");
			 	posRight = operation[1].find(")",pos);
			 	operation[1].replace(posRight,1,"]");

			 }

			 while(1)
			 {
			 	int pos = operation[1].find("zeros("); int posRight;
			 	if(pos==-1) break;
			 	operation[1].replace(pos,6,"zeros[");
			 	posRight = operation[1].find(")",pos);
			 	operation[1].replace(posRight,1,"]");

			 }


			  while(1)
			 {
			 	int pos = operation[1].find("rand("); int posRight;
			 	if(pos==-1) break;
			 	operation[1].replace(pos,5,"rand[");
			 	posRight = operation[1].find(")",pos);
			 	operation[1].replace(posRight,1,"]");

			 }

			 while(1)
			 {
			 	int pos = operation[1].find("ones("); int posRight;
			 	if(pos==-1) break;
			 	operation[1].replace(pos,5,"ones[");
			 	posRight = operation[1].find(")",pos);
			 	operation[1].replace(posRight,1,"]");

			 }


			 while(1)
			 {
			 	int pos = operation[1].find("sqrt("); int posRight;
			 	if(pos==-1) break;
			 	operation[1].replace(pos,5,"sqrt[");
			 	int parentheses = 1;
			 	for (int i = pos+1; i < operation[1].length(); ++i)
			 	{
			 		if(operation[1][i] == '(')
			 			parentheses++;
			 		if(operation[1][i] == ')')
			 			parentheses--;

			 		if(parentheses==0)
			 		{
			 			pos = i;
			 			break;
			 		}
			 	}

			 	
			 	operation[1].replace(pos,1,"]");
			 }

			  while(1)
			 {
			 	int pos = operation[1].find("sin("); int posRight;
			 	if(pos==-1) break;
			 	operation[1].replace(pos,4,"sin[");

			 	int parentheses = 1;
			 	for (int i = pos+1; i < operation[1].length(); ++i)
			 	{
			 		if(operation[1][i] == '(')
			 			parentheses++;
			 		if(operation[1][i] == ')')
			 			parentheses--;

			 		if(parentheses==0)
			 		{
			 			pos = i;
			 			break;
			 		}
			 	}

			 	
			 	operation[1].replace(pos,1,"]");
			 }

			  while(1)
			 {
			 	int pos = operation[1].find("cos("); int posRight;
			 	if(pos==-1) break;
			 	operation[1].replace(pos,4,"cos[");
			 	int parentheses = 1;
			 	for (int i = pos+1; i < operation[1].length(); ++i)
			 	{
			 		if(operation[1][i] == '(')
			 			parentheses++;
			 		if(operation[1][i] == ')')
			 			parentheses--;

			 		if(parentheses==0)
			 		{
			 			pos = i;
			 			break;
			 		}
			 	}

			 	
			 	operation[1].replace(pos,1,"]");

			 }

			  while(1)
			 {
			 	int pos = operation[1].find("tan("); int posRight;
			 	if(pos==-1) break;
			 	operation[1].replace(pos,4,"tan[");
			 	int parentheses = 1;
			 	for (int i = pos+1; i < operation[1].length(); i++)
			 	{
			 		if(operation[1][i] == '(')
			 			parentheses++;
			 		if(operation[1][i] == ')')
			 			parentheses--;

			 		if(parentheses==0)
			 		{
			 			pos = i;
			 			break;
			 		}
			 	}

			 	
			 	operation[1].replace(pos,1,"]");
			 }

			 //======================================
		Matrix result = parentheses(operation[1]);
		deleteTemporaries(); 
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
 		if(s.find("[")!=-1)
 		{
 		
 			string s2;
 			while(countBrackets(s)>0) 
 			{
 				getline(file1,s2);
 				s+= s2;
 			}

		} 
		for (int i = 0; i < s.length(); ++i)
		{
			if(s[i] == '\r' || s[i]== '\n' )
				s.erase(i,1);
		} 	
		if(s.length()!=0)
 		 handle(s); 
 	} 

 	 file1.close();
 }


void Parser::handle(string line)
{
	if(line.find("=")==-1)
	{
		line = string("ans = ") + line;
	}

	int doesPrint = 1;
	if(line[line.length()-1]==';')
	{
		doesPrint = 0;
		line.erase(line.length()-1);
	}

	string* sides;
	int numberOfSides = split(line, "=", &sides);


	for (int i = numberOfSides - 1; i>1; i--)
	{
		handleLine(sides[i - 1] + string("=") + sides[i], 0);
	}
	handleLine(sides[0] + string("=") + sides[1], doesPrint);

}



int Parser::isNumber(string s)
{
	for (int i = 0; i < s.length(); ++i)
	{
		
		if(!(  (s[i]>47 && s[i]<58) || s[i]=='.' || s[i]== '-') )
			{return 0;}
	}

	return 1;
}


void Parser::inverseAndTransbose(string var)
{ 
	int positionInverse = var.find("inv[");
	int positionSqrt = var.find("sqrt[");
	int positionSin = var.find("sin[");
	int positionCos = var.find("cos[");
	int positionTan = var.find("tan[");
	int positionTransbose = var.rfind("\'");

	if(positionInverse == 0)
	{
		string original = var;
			if(positionTransbose == (var.length()-1))
				original.erase(var.length()-1,1);
		original.erase(0,4);

		original.erase(original.length()-1,1);

		 Matrix originalM = parentheses(original);
		 string onlyInverse = var;

		 if(positionTransbose == (var.length()-1))
				onlyInverse.erase(var.length()-1,1);


		Matrix* added = findOrAdd(onlyInverse,originalM.getColumns(),originalM.getRows());
		*added = originalM.inverse();



	}

	else if(positionSqrt == 0)
	{	
		string original = var; 		
			if(positionTransbose == (var.length()-1))
				original.erase(var.length()-1,1);
		original.erase(0,5);

		original.erase(original.length()-1,1); 

		 Matrix originalM = parentheses(original);
		 string onlyInverse = var;

		 if(positionTransbose == (var.length()-1))
				onlyInverse.erase(var.length()-1,1);


		Matrix* added = findOrAdd(onlyInverse,originalM.getColumns(),originalM.getRows());
		*added = originalM.msqrt();


	}

	else if(positionSin == 0)
	{
		string original = var;
			if(positionTransbose == (var.length()-1))
				original.erase(var.length()-1,1);
		original.erase(0,4);  

		original.erase(original.length()-1,1);

		 Matrix originalM = parentheses(original);
		 string onlyInverse = var;

		 if(positionTransbose == (var.length()-1))
				onlyInverse.erase(var.length()-1,1);


		Matrix* added = findOrAdd(onlyInverse,originalM.getColumns(),originalM.getRows());
		*added = originalM.msin();



	}


	else if(positionCos == 0)
	{
		string original = var;
			if(positionTransbose == (var.length()-1))
				original.erase(var.length()-1,1);
		original.erase(0,4);  

		original.erase(original.length()-1,1);

		 Matrix originalM = parentheses(original);
		 string onlyInverse = var;

		 if(positionTransbose == (var.length()-1))
				onlyInverse.erase(var.length()-1,1);


		Matrix* added = findOrAdd(onlyInverse,originalM.getColumns(),originalM.getRows());
		*added = originalM.mcos();



	}


else if(positionTan == 0)
	{
		string original = var;
			if(positionTransbose == (var.length()-1))
				original.erase(var.length()-1,1); 
		original.erase(0,4);  

		original.erase(original.length()-1,1);

		 Matrix originalM = parentheses(original);
		 string onlyInverse = var;

		 if(positionTransbose == (var.length()-1))
				onlyInverse.erase(var.length()-1,1);


		Matrix* added = findOrAdd(onlyInverse,originalM.getColumns(),originalM.getRows());
		*added = originalM.mtan();



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
	 
 
		
		Matrix result;

		string* seps;
		int numberOfSeparators;
		string* variables;
		int numberOfVariables;

		numberOfVariables = split(line, "+-", &variables, &numberOfSeparators, &seps);



		if(isNumber(variables[0])) // setting result to first variable
		{
			result.setConstant(atof(variables[0].c_str()));

		}

		else result = mulAndDivide(variables[0]);

			

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


		if(isNumber(variables[0])) // setting result to first variable
		{
			result.setConstant(atof(variables[0].c_str()));
		}

		else 
			{
				result = power(variables[0]);
			}



			for (int i = 0; i<numberOfSeparators; i++)
		{
			
			
			if (!seps[i].compare("*"))
			{

				if(isNumber(variables[i+1]))
			 			{
			 				double val = atof(variables[i+1].c_str());
			 				result = result.dotProduct(val);
			 			}

						else

						result = result * (power(variables[i + 1]));
			}


			else if (!seps[i].compare("/"))
			{
				
				if(isNumber(variables[i+1]))
			 			{
			 				double val = atof(variables[i+1].c_str());
			 				result = result.dotDivision(val);
			 			}

						else

						result = result / (power(variables[i + 1]));
			}

			 else if(!seps[i].compare("$"))
			 		{
			 			if(isNumber(variables[i+1]))
			 			{
			 				double val = atof(variables[i+1].c_str());
			 				result = result.dotDivision(val);
			 			}

						else

			 				result = result.dotDivision(power(variables[i + 1]));

			 		}

			 else if(!seps[i].compare("#"))
			 		{
						if(isNumber(variables[i+1]))
					 			{
					 				double val = atof(variables[i+1].c_str());
					 				result = result.dotProduct(val);
					 			}
					 		
					 	else

			 				result = result.dotProduct(power(variables[i + 1]));

			 		}
			 
		}


		return result;
		
	}


	Matrix Parser::power(string line)
	{
		Matrix result;
		string* seps;
		int numberOfSeparators;
		string* variables;
		int numberOfVariables;

		numberOfVariables = split(line, "^%", &variables, &numberOfSeparators, &seps);

		for(int i=0; i<numberOfVariables; i++)
			inverseAndTransbose(variables[i]);

		if(isNumber(variables[0])) // setting result to first variable
		{
			result.setConstant(atof(variables[0].c_str()));
		}

		else 
			{
				result = *find(variables[0]);
			}





			for (int i = 0; i<numberOfSeparators; i++)
		{
			
			
			if (!seps[i].compare("^"))
			{

				if(isNumber(variables[i+1]))
			 			{
			 				double val = atof(variables[i+1].c_str());
			 				result = (result^val);
			 			}

						else

						result = (result ^ (*(find(variables[i + 1]))));
			}



			if (!seps[i].compare("%"))
			{

				if(isNumber(variables[i+1]))
			 			{
			 				double val = atof(variables[i+1].c_str());
			 				result = (result.dotPower(val));
			 			}

						else

						result = (result.dotPower((*(find(variables[i + 1])))));
			}



		}


		return result;
		
	}

int Parser::splitParentheses(string s, string separators, string** result, int* numberOfSeparators, string** seps)
{

	int parentheses= 0;

	int numberOfElements = 1; int counter = 0; int lastPosition = 0; int Separators = 0; int sepsCounter = 0;
	for (int i = 0; i<s.length(); i++)
	{
		for (int j = 0; j<separators.length(); j++)
		{

		if(s[i]=='[') //skip till ']'
		{
			i = s.find(']',i);
		}
			if(s[i]=='(') parentheses++;
			else if(s[i]==')') parentheses--;
			if (s[i] == separators[j] && parentheses==0)
			{
				numberOfElements++;
				Separators++;
			}
		}
	}

	parentheses = 0;

	*seps = new string[Separators];
	*result = new string[numberOfElements];

	for (int i = 0; i<s.length(); i++)
	{
		


		for (int j = 0; j<separators.length(); j++)
		{

		if(s[i]=='[') //skip till ']'
		{
			i = s.find(']',i);
		}
			if(s[i]=='(') parentheses++;
			else if(s[i]==')') parentheses--;
			if (s[i] == separators[j] && parentheses==0)
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

	
	for(int i=0; i<numberOfElements; i++)
	{
		if((*result)[i][0] == '(')
			(*result)[i].erase(0,1);

		if((*result)[i][(*result)[i].length()-1] == ')')
			(*result)[i].erase((*result)[i].length()-1,1);

	}
	return counter;

}


Matrix Parser::parentheses(string line)
{ 
	string operation; static int temporaryNumber=0;
	Matrix result;
		string* seps;
		int numberOfSeparators;
		string* variables;
		int numberOfVariables;
		numberOfVariables = splitParentheses(line, "/*+-$#^", &variables, &numberOfSeparators, &seps); 
		Matrix *variableMatrices = new Matrix[numberOfVariables];

		for (int i = 0; i < numberOfVariables; ++i)
		{
			int num=0;// 3shan tfawet eli gwa [  ]
			for (int j = 0; j < variables[i].length(); ++j)
			{
				if(variables[i][j]=='[')
					j = variables[i].find("]",i);
				if(variables[i][j] == '(' || variables[i][j]==')')
					num ++;

			}

			if(num!= 0)
				variableMatrices[i] = parentheses(variables[i]);
			else
				variableMatrices[i] = plusAndMinus(variables[i]);

			string name = string(FAKE_NAME) + SSTR(temporaryNumber);
			Matrix* temp = findOrAdd(name,variableMatrices[i].getRows(),variableMatrices[i].getColumns());
				*temp = variableMatrices[i];

				operation+= name;
				
				if(i<numberOfVariables-1)
					operation+= seps[i];

				temporaryNumber++;
		}
		return plusAndMinus(operation);

}


void Parser::deleteTemporaries()
{
	for (int i = 0; i < matrices.size(); ++i)
	{
		 if(matrices[i]->getName().find(FAKE_NAME)!=-1)
		 {
		 	matrices[i]->destroy();
		 	matrices.erase(matrices.begin()+i);

		 }
	}
}

	int Parser::countBrackets(string s)
	{
		int counter=0;

		for (int i = 0; i < s.length(); ++i)
		{
			if(s[i]=='[')
				counter++;

			if(s[i]==']')
				counter--;
		}

		return counter;
	}
