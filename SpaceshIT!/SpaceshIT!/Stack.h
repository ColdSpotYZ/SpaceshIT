//Stack.h (Pointer-based implementation)
#pragma once
#include <iostream>
using namespace std;

// typedef int ItemType;
typedef string ItemType;

template <class T>
class Stack
{
private:
	struct Node
	{
		T item;
		Node<T>* next;
	};

	Node<T>* topNode;

public:
	//Default constructor
	Stack();
	//Destructor
	~Stack();

	//check if the stack is empty
	bool isEmpty();

	//push item on top of the stack
	bool push(ItemType& item);

	//pop item from top of stack
	bool pop();

	//retrieve and pop item from top of stack
	bool pop(ItemType& item);

	//retrieve item from top of stack
	void getTop(ItemType& item);

	//display items in stack in order
	void displayInOrder();

};

///////////////////////////////
///     IMPLEMENTATIONS     ///
//////////////////////////////

template<class T>
Stack<T>::Stack() { this->topNode = NULL; }

template<class T>
Stack<T>::~Stack()
{
	while (!isEmpty())
	{
		pop();
	}

}

template<class T>
bool Stack<T>::isEmpty()
{
	if (topNode == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool Stack<T>::push(ItemType& item)
{
	if (!isEmpty())
	{
		Node* temp = new Node;
		temp->item = item;
		temp->next = topNode;
		topNode = temp;
		return true;
	}
	else
	{
		Node* temp = new Node;
		temp->item = item;
		temp->next = NULL;
		topNode = temp;
		return true;
	}

}

template<class T>
bool Stack<T>::pop()
{
	bool success = !isEmpty();
	if (success)
	{
		Node* temp = topNode;
		topNode = topNode->next;
		temp->next = NULL;
		delete temp;
		temp = NULL;
	}
	return success;
}

template<class T>
bool Stack<T>::pop(ItemType& item)
{
	bool success = !isEmpty();
	if (success)
	{
		Node* temp = topNode;
		item = temp->item;
		topNode = topNode->next;
		temp->next = NULL;
		delete temp;
		temp = NULL;
	}
	return success;
}

template<class T>
void Stack<T>::getTop(ItemType& item)
{
	if (!isEmpty())
	{
		item = topNode->item;
	}
}

template<class T>
void Stack<T>::displayInOrder()
{
	ItemType item;
	if (!isEmpty())
	{
		while (!isEmpty())
		{
			getTop(item);
			cout << item << endl;
			pop();
		}
	}
}
