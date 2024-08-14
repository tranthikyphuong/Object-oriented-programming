#pragma once
template <typename T>
class Node
{
private:
	T data;
	Node* next;
	Node* prev;
public:
	Node();
	Node(T value);
	T getData();
	Node* getNext();
	void setNext(Node* next);
	Node* getPrev();
	void setPrev(Node* prev);
	void setData(T value);
	~Node();
};
