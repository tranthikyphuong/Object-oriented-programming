#include "Expression.h"
#include "Stack.h"
#include "MathHelper.h"
#include <string>

Expression::Expression()
{
	this->content = "";
}

Expression::Expression(string content)
{
	this->content = content;
}

void Expression::setContent(string content)
{
	this->content = content;
}

LinkedList<string>* Expression::splitAll()
{
	LinkedList<string>* list = new LinkedList<string>();
	for (int index = 0; index < content.length(); )
	{
		int stepper = index;
		string result = "";

		if ((content[stepper] >= '0' && content[stepper] <= '9') || (content[stepper] == '.')) {
			while ((content[stepper] >= '0' && content[stepper] <= '9') || (content[stepper] == '.'))
			{
				result += content[stepper];
				stepper++;
			}
		}
		else if ((content[stepper] >= 'a' && content[index] <= 'z'))
		{
			while ((content[stepper] >= 'a' && content[index] <= 'z'))
			{
				result += content[stepper];
				stepper++;
			}
		}

		if (stepper == index) {
			list->add(std::string(1, content[index]));
			index++;
		}
		else {
			list->add(result);
			index = stepper;
		}
	}
	return list;
}

LinkedList<string>* Expression::toPostfix()
{
	Stack<string>* stack = new Stack<string>();
	LinkedList<string>* postfix = new LinkedList<string>();
	LinkedList<string>* elements = this->splitAll();
	Node<string>* traveller = elements->getHead();
	while(traveller != nullptr)
	{
		string token = traveller->getData();
		if (MathHelper::getInstance()->isNumber(token))
		{
			postfix->add(token);
		}
		else if (MathHelper::getInstance()->isOpeningBracket(token))
		{
			stack->push(token);
		}
		else if (MathHelper::getInstance()->isClosingBracket(token))
		{
			while (!stack->isEmpty() && !MathHelper::getInstance()->isOpeningBracket(stack->getTop()))
			{
				postfix->add(stack->pop());
			}
			if (MathHelper::getInstance()->isOpeningBracket(stack->getTop()))
			{
				stack->pop();
			}
		}
		else {
			while (!stack->isEmpty() && MathHelper::getInstance()->isOperator(stack->getTop()) 
				&& MathHelper::getInstance()->getPriority(stack->getTop()) >= MathHelper::getInstance()->getPriority(token)) {
				postfix->add(stack->pop());
			}
			stack->push(token);
		}
		traveller = traveller->getNext();
	}
	while (!stack->isEmpty()) 
	{
		postfix->add(stack->pop());
	}
	return postfix;
}

double Expression::calculate()
{
	Stack<double>* stack = new Stack<double>();
	LinkedList<string> *postfix = this->toPostfix();
	Node<string>* traveller = postfix->getHead();
	while (traveller != nullptr)
	{
		string token = traveller->getData();
		if (MathHelper::getInstance()->isNumber(token))
		{
			stack->push(stod(token));
		}
		else {
			if (token.length() == 1)
			{
				double first = stack->pop();
				double second = stack->pop();
				stack->push(MathHelper::getInstance()->solveWithOperator(token, second, first));
			}
			else
			{
				double first = stack->pop();
				stack->push(MathHelper::getInstance()->solveWithOperator(token, first));
			}
		}
		traveller = traveller->getNext();
	}
	if (stack->getSize() > 2) 
	{
		throw "Invalid expression";
	}
	return stack->pop();
}