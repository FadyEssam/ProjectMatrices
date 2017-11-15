#ifndef PARSERHH
#define PARSERHH
#include <vector>
#include "Matrix.h"
#include <string>
#include <sstream>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
            ( std::ostringstream() << std::dec << x ) ).str()



using namespace std;
class Parser
{
private:
	vector<Matrix*> matrices;
	int splitParentheses(string s, string separators, string** result, int* numberOfSeparators, string** seps);
	int split(string s, string separators, string** result, int* numberOfSeparators, string** seps);
	int split(string s, string separators, string** result); // returns number of strings
	string removeAllSpaces(string s);
	Matrix* find(string name);
	Matrix* add(string name, int rows, int columns);
	Matrix* findOrAdd(string name, int rows, int columns);
	void handleLine(string line, int print);
	int isNumber(string s);
	void inverseAndTransbose(string var);
	Matrix plusAndMinus(string line);
	Matrix mulAndDivide(string line);
	Matrix power(string line);
	void deleteTemporaries();
	Matrix parentheses(string line);
	Matrix commasAndSpaces(string s);
	Matrix semiColumns(string s);
	string replace(string operation);

public:
	Parser();
	~Parser();
	int splitBrackets(string s, string separators, string** result);
	string removeSidesSpaces(string s);
	void handle(string line);
	void load(string filePath);
	int countBrackets(string s);



};
#endif