#include <iostream>
#include "Matrix.h"
#include "Parser.h"
using namespace std;

int main(int argc, char const *argv[])
{

	Parser parser;

	if(argc>1)

		{
			 parser.load(argv[1]);
		}

	else

		{
			string s;
			while (1)
			{
				getline(cin, s);
				if (!s.compare("exit")) break;
				parser.handle(s);
			}

		}

	return 0;
}