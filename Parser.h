#ifndef PARSERHH
#define PARSERHH
#include <vector>
#include "Matrix.h"
#include <string>
using namespace std;
class Parser
{
private:
	vector<Matrix*> matrices;
	int size;
	int split(string s, string separators, string** result, int* numberOfSeparators, string** seps);
	int split(string s, string separators, string** result); // returns number of strings
	string removeSidesSpaces(string s);
	string removeAllSpaces(string s);
	Matrix* find(string name);
	Matrix* add(string name, int rows, int columns);
	Matrix* findOrAdd(string name, int rows, int columns);
	void handleLine(string line, int print);
	int isNumber(string s);

public:
	Parser();
	void handle(string line);
	void load(string filePath);



};
#endif