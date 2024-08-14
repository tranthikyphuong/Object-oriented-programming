#pragma once
#include "Node.h"

template <typename T>
class LinkedList
{
private: 
	Node<T>* head;
	Node<T>* tail;
public:
	LinkedList();
	void add(T value);
	T removeTail();
	Node<T>* getTail();
	Node<T>* getHead();
	bool isEmpty();
	~LinkedList();
};
