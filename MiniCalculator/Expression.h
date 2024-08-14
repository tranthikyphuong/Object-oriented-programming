#pragma once
#include <iostream>
#include "LinkedList.h"

using namespace std;

class Expression
{
private:
	string content;
public:
	Expression();
	Expression(string content);
	void setContent(string content);
	double calculate();
	LinkedList<string>* splitAll();
	LinkedList<string>* toPostfix();
};

