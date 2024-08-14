#pragma once
#include <iostream>
#include <math.h>

using namespace std;

class MathHelper
{
private:
	static MathHelper *instance;
	string operators[13] = { "+", "-", "*", "/", "^", "sqrt", "abs", "sin", "cos", "tan", "log", "ln", "exp"};
	int numberOfOps = 13;
	MathHelper();
public:
	static MathHelper* getInstance();
	bool isOperator(string token);
	bool isNumber(string token);
	bool isOpeningBracket(string token);
	bool isClosingBracket(string token);
	double solveWithOperator(string op, double a, double b);
	double solveWithOperator(string op, double a);
	int getPriority(string token);
	~MathHelper();
};

