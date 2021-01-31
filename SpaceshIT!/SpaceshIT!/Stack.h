//Stack.h (Pointer-based implementation)
#pragma once
#include <iostream>
using namespace std;

// typedef int T;

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
	bool push(T& item);

	//pop item from top of stack
	bool pop();

	//retrieve and pop item from top of stack
	bool pop(T& item);

	//retrieve item from top of stack
	T& getTop();

	//retrieve item from top of stack
	void getTop(T& item);

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
bool Stack<T>::push(T& item)
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
bool Stack<T>::pop(T& item)
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
inline T& Stack<T>::getTop()
{
	if (!isEmpty())
	{
		return topNode->item;
	}
}

template<class T>
void Stack<T>::getTop(T& item)
{
	if (!isEmpty())
	{
		item = topNode->item;
	}
}

template<class T>
void Stack<T>::displayInOrder()
{
	T item;
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
