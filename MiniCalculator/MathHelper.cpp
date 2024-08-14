#include "MathHelper.h"
#include <string>

using namespace std;

bool isNumber(const string& str)
{
	for (char const& c : str) {
		if (isdigit(c) == 0) return false;
	}
	return true;
}

MathHelper* MathHelper::instance = nullptr;

MathHelper::MathHelper()
{

}

MathHelper* MathHelper::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MathHelper();
	}
	return instance;
}

bool MathHelper::isNumber(string token)
{
	int countPoint = 0;
	for (int index = 0; index < token.length(); index++) {
		if (token[index] == '.')
		{
			if (index == 0 || index == token.length() - 1)
			{
				throw "Invalid expression";
			}
			countPoint += 1;
		}
		else if (isdigit(token[index]) == 0) return false;
	}
	if (countPoint > 1)
	{
		throw "Invalid expression";
	}
	return true;
}

bool MathHelper::isOperator(string token)
{
	for (int index = 0; index < this->numberOfOps; index++)
	{
		if (operators[index] == token)
		{
			return true;
		}
	}
	return false;
}

bool MathHelper::isOpeningBracket(string token)
{
	return token == "(";
}

bool MathHelper::isClosingBracket(string token)
{
	return token == ")";
}

int MathHelper::getPriority(string token)
{
	for (int index = 0; index < this->numberOfOps; index++)
	{
		if (operators[index] == token)
		{
			if (index < 2) 
			{
				return 0;
			}
			if (index < 4) 
			{
				return 1;
			}
			if (index > 4)
			{
				return 5;
			}
			return index;
		}
	}
	throw "Invalid operator";
}

double MathHelper::solveWithOperator(string op, double a, double b)
{
	if (op == "+") {
		return a + b;
	}
	if (op == "-") {
		return a - b;
	}
	if (op == "*") {
		return a * b;
	}
	if (op == "/") {
		if (b == 0) {
			throw "Can't divide by zero";
		}
		return a / b;
	}
	if (op == "^") {
		return pow(a, b);
	}
	throw "Invalid expression";
}

double MathHelper::solveWithOperator(string op, double a)
{
	if (op == "sqrt") 
	{
		return sqrt(a);
	}
	if (op == "abs")
	{
		return abs(a);
	}
	if (op == "sin")
	{
		return sin(a);
	}
	if (op == "cos")
	{
		return cos(a);
	}
	if (op == "tan")
	{
		return tan(a);
	}
	if (op == "log")
	{
		return log10(a);
	}
	if (op == "ln")
	{
		return log(a);
	}
	if (op == "exp")
	{
		return exp(a);
	}
	throw "Invalid expression";
}

MathHelper::~MathHelper()
{
	delete instance;
}