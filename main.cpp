#include <iostream>
#include "Matrix.h"
#include "Parser.h"
#include <stdlib.h>
using namespace std;
Parser parser;


int main()
{

	string s;
	while(1)
	{
		getline(cin,s);
		if(!s.compare("exit")) break;
		parser.handleLine(s);
	}
	
return 0;
}