#include "LinkedList.h"
#include <iostream>

template class LinkedList<int>;
template class LinkedList<float>;
template class LinkedList<double>;
template class LinkedList<long>;
template class LinkedList<long long>;
template class LinkedList<std::string>;
template class LinkedList<char>;

template <typename T>
LinkedList<T>::LinkedList()
{
	this->head = nullptr;
	this->tail = nullptr;
}

template <typename T>
void LinkedList<T>::add(T value)
{
	Node<T>* node = new Node<T>(value);
	if (this->isEmpty())
	{
		this->head = node;
		this->tail = node;
		return;
	}
	this->tail->setNext(node);
	node->setPrev(this->tail);
	this->tail = node;
}

template <typename T>
bool LinkedList<T>::isEmpty()
{
	return this->tail == nullptr;
}

template <typename T>
T LinkedList<T>::removeTail()
{
	if (this->isEmpty()) return T();
	T removedValue;
	if (this->head == this->tail)
	{
		removedValue = this->tail->getData();
		delete this->head;
		this->head = nullptr;
		this->tail = nullptr;
		return removedValue;
	}

	Node<T>* traveller = this->head;
	while (traveller->getNext() != this->tail)
	{
		traveller = traveller->getNext();
	}
	removedValue = this->tail->getData();
	delete this->tail;
	this->tail = traveller;
	this->tail->setNext(nullptr);
	return removedValue;
}

template <typename T>
Node<T>* LinkedList<T>::getTail()
{
	return this->tail;
}

template <typename T>
Node<T>* LinkedList<T>::getHead()
{
	return this->head;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	Node<T>* traveller = this->head;
	while (traveller != nullptr)
	{
		Node<T>* removableNode = traveller;
		traveller = traveller->getNext();
		delete removableNode;
	}
}