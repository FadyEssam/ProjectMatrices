#include <iostream>
#include "Matrix.h"
#include "Parser.h"
#include "Complex.h"
#include<cmath>
using namespace std;

extern int lineNumber;
int main(int argc, char const *argv[])
{

	Parser parser; 

 
	if(argc>1)
	{
		try
		{
			{
				 parser.load(argv[1]);
			}
		}

		catch(const char* e)
		{
			cout<<"Error at line number "<<lineNumber<<": "<<e<<endl;
		}

		catch(string e)
		{
			cout<<"Error at line number "<<lineNumber<<": "<<e<<endl;
		}


	}

	else

		{
			string s; int exit =0;
			while (1)
			{
				try
				{
									getline(cin, s);

									if(s.find("[")!=-1)
					 		{
					 		
					 				string s2;
					 				while(parser.countBrackets(s)>0) 
					 				{
					 					getline(cin,s2);

					 					s = parser.removeSidesSpaces(s);
			 							s2 = parser.removeSidesSpaces(s2);
			 							if(string(";[=").find(s[s.length()-1])==-1 && s2[0] != ';')
			 							s+= string(";");

					 					s+= s2;
					 				}

								} 
							
								for (int i = 0; i < s.length(); ++i)
								{
									if(s[i] == '\r' || s[i]== '\n' )
									s.erase(i,1);
								} 	


									if (!s.compare("exit")){exit =1; break;}
									parser.handle(s);
				}



							catch(const char* e)
							{
								cout<<e<<endl;
								if(exit==1) break;
							}

							catch(string e)
							{
								cout<<e<<endl;
								if(exit==1) break;
							}

			}




		}

	return 0;
}

