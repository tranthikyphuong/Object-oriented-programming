#include "Stack.h"
#include <iostream>

template class Stack<int>;
template class Stack<float>;
template class Stack<double>;
template class Stack<long>;
template class Stack<long long>;
template class Stack<std::string>;
template class Stack<char>;

template <typename T>
Stack<T>::Stack()
{
	this->container = new LinkedList<T>();
	this->top = -1;
}

template <typename T>
void Stack<T>::push(T value)
{
	this->container->add(value);
	this->top += 1;
}

template <typename T>
T Stack<T>::pop()
{
	this->top -= 1;
	return this->container->removeTail();
}

template <typename T>
T Stack<T>::getTop()
{
	if (top < 0)
	{
		return T();
	}
	return this->container->getTail()->getData();
}

template <typename T>
bool Stack<T>::isEmpty()
{
	return this->container->isEmpty();
}

template <typename T>
int Stack<T>::getSize()
{
	return this->top + 1;
}

template <typename T>
Stack<T>::~Stack()
{
	delete this->container;
}