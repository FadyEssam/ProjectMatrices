#include "Parser.h"
#include <stdlib.h>
#define ROWS_SEPARATOR ";"
#define COLUMN_SEPARATOR " "


Parser::Parser()
{
	size=0;
}


int Parser::split(string s,string separators,string** result)
{
	int numberOfElements= 1; int counter=0; int lastPosition=0;
	for(int i=0; i<s.length(); i++)
	{
		for (int j=0; j<separators.length(); j++)
		{
			if(s[i]==separators[j])
			{
				numberOfElements++;
			}
		}
	}


	 *result= new string[numberOfElements];

	for(int i=0; i<s.length(); i++)
	{
		for (int j=0; j<separators.length(); j++)
		{
			if(s[i]==separators[j])
			{
				(*result)[counter] = s.substr(lastPosition,i-lastPosition);
				lastPosition=i+1;
				counter++;
				while(separators.find(s[i])!=-1) i++;
			}
		}
	}
	if(lastPosition!=s.length())
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


int Parser::split(string s,string separators,string** result,int* numberOfSeparators, string** seps)
{
	int numberOfElements= 1; int counter=0; int lastPosition=0; int Separators=0; int sepsCounter=0;
	for(int i=0; i<s.length(); i++)
	{
		for (int j=0; j<separators.length(); j++)
		{
			if(s[i]==separators[j])
			{
				numberOfElements++;
				Separators++;
			}
		}
	}

	 *seps = new string[Separators];
	 *result= new string[numberOfElements];

	for(int i=0; i<s.length(); i++)
	{
		for (int j=0; j<separators.length(); j++)
		{
			if(s[i]==separators[j])
			{	(*seps)[sepsCounter] = separators[j];
				sepsCounter++;
				(*result)[counter] = s.substr(lastPosition,i-lastPosition);
				lastPosition=i+1;
				counter++;
			}
		}
	}
	if(lastPosition!=s.length())
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
	int start=0;
	for(int i=0; i<s.length(); i++)		
		if(s[i]==' ')
		start++;
		else break;
	


	string result = s.substr(start);

	for(int i=result.length()-1; i>=0; i--)
		if(result[i]==' ')
		result.erase(i,1);
		else break;


	return result;

}

string Parser::removeAllSpaces(string s)
{
	for(int i=s.length()-1; i>=0; i--)
		if(s[i]==' ')
			s.erase(i,1);

	return s;
}


Matrix* Parser::find(string name)

{

	for(int i=0; i<size; i++)
	{
		if(name==matrices[i]->getName())
			return matrices[i];
	}

	return NULL;
}
 

Matrix* Parser::add(string name,int rows, int columns)
{
	Matrix* added = new Matrix(rows,columns,name);

	matrices.push_back(added);
	size++;

	return added;
}

Matrix* Parser::findOrAdd(string name, int rows, int columns)
{
	 Matrix* found = find(name);

	 if(found==NULL)
	 	found = add(name,rows,columns);

	return found;
}


void Parser::handleLine(string line)
{

	if( line.find("[")!= -1) //it is declaring a new matrix
	{
		string* operation;
		split(line,"=",&operation);

		operation[0] = removeAllSpaces(operation[0]);
		operation[1] = removeSidesSpaces(operation[1]);
		operation[1].erase(operation[1].find("["),1); 
		operation[1].erase(operation[1].find("]"),1); //remove "[,]"
		string* rows;
		int numberOfRows = split(operation[1],ROWS_SEPARATOR,&rows);  
		int numberOfColumns;
		string** elementsCut;


		for(int i=0; i<numberOfRows; i++)
		{
			rows[i] = removeSidesSpaces(rows[i]);
			numberOfColumns = split(rows[i], COLUMN_SEPARATOR, &(elementsCut[i]) );
		}

		Matrix* host = findOrAdd(operation[0],numberOfRows, numberOfColumns);

		for(int i=0; i<numberOfRows; i++)
			for(int j=0; j<numberOfColumns; j++)
			{
				elementsCut[i][j] = removeAllSpaces(elementsCut[i][j]);
				(*host)[i][j] = atof(elementsCut[i][j].c_str());
			}
			cout<<(*host);
	}



	else //it's an operation on existing matrix
	{
		line = removeAllSpaces(line);
		string* operation;
		split(line,"=",&operation);
		Matrix result;

		string* seps;
		int numberOfSeparators;
		string* variables;
		int numberOfVariables;

		numberOfVariables = split(operation[1],"+-/*\'",&variables,&numberOfSeparators,&seps);

		result = *find(variables[0]);
		for(int i=0; i<numberOfSeparators; i++)
		{
			if(!seps[i].compare("+"))
				result = result + *(find(variables[i+1]));
			else if(!seps[i].compare("-"))
				result = result - *(find(variables[i+1]));
			else if(!seps[i].compare("/"))
				result = result / *(find(variables[i+1]));
			else if(!seps[i].compare("*"))
				result = result * (*(find(variables[i+1])));
			else if(!seps[i].compare("/"))
				result = result / (*find(variables[i+1]));
			else if(!seps[i].compare("\'"))
					result = result.inverse();
		}

		Matrix* host = findOrAdd(operation[0],result.getRows(),result.getColumns());
		(*host) = result;
		cout<<(*host);
	}


}