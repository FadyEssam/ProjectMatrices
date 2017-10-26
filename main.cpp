#include <iostream>
#include "Matrix.h"
#include "Parser.h"
using namespace std;

int main()
{
	Parser parser;
	 string path = "/home/fady/matrices/commands";
	 parser.load(path);
	
	/*string s;
	while (1)
	{
		getline(cin, s);
		if (!s.compare("exit")) break;
		parser.handle(s);
	}*/
	return 0;
}