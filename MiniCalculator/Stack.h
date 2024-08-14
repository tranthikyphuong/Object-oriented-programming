#pragma once
#include "LinkedList.h"

template <typename T>
class Stack
{
private:
	int top;
	LinkedList<T> *container;
public:
	Stack();
	void push(T node);
	T pop();
	T getTop();
	bool isEmpty();
	int getSize();
	~Stack();
};
