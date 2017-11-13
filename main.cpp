#include <iostream>
#include "Matrix.h"
#include "Parser.h"
#include<cmath>
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

						if(s.find("[")!=-1)
		 			{
		 		
		 				string s2;
		 				while(parser.countBrackets(s)>0) 
		 				{
		 					getline(cin,s2);
		 					s+= s2;
		 				}

					} 
				
					for (int i = 0; i < s.length(); ++i)
					{
						if(s[i] == '\r' || s[i]== '\n' )
						s.erase(i,1);
					} 	


						if (!s.compare("exit")) break;
						parser.handle(s);
			}

		}

	return 0;
}

