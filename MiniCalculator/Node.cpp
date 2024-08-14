#include "Node.h"
#include <iostream>

template class Node<int>;
template class Node<float>;
template class Node<double>;
template class Node<long>;
template class Node<long long>;
template class Node<std::string>;
template class Node<char>;

template <typename T>
Node<T>::Node()
{
	this->data = T();
	this->next = nullptr;
	this->prev = nullptr;
}

template <typename T>
Node<T>::Node(T value)
{
	this->data = value;
	this->next = nullptr;
	this->prev = nullptr;
}

template <typename T>
T Node<T>::getData()
{
	return this->data;
}

template <typename T>
void Node<T>::setData(T value)
{
	this->data = value;
}

template <typename T>
void Node<T>::setNext(Node<T>* next)
{
	this->next = next;
}

template <typename T>
Node<T>* Node<T>::getNext()
{
	return this->next;
}

template <typename T>
void Node<T>::setPrev(Node<T>* prev)
{
	this->prev = prev;
}

template <typename T>
Node<T>* Node<T>::getPrev()
{
	return this->prev;
}

template <typename T>
Node<T>::~Node()
{
	this->next = nullptr;
	this->prev = nullptr;
}