//Stack.h (Pointer-based implementation)
#pragma once
#include <iostream>
using namespace std;

// typedef int T;

const int MAX_SIZE = 10;

template <class T>
class Stack
{
private:
	T state[MAX_SIZE];

	int size;

public:
	//Default constructor
	Stack();
	//Destructor
	~Stack();

	//check if the stack is empty
	bool isEmpty();

	//push item on top of the stack
	bool push(T item);

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
Stack<T>::Stack() 
{ 
	for (int i = 0; i < MAX_SIZE; i++)
	{
		state[i] = nullptr;
	}
	size = 0;
}

template<class T>
Stack<T>::~Stack()
{
	while (!isEmpty())
	{
		pop();
	}
	size = 0;

}

template<class T>
bool Stack<T>::isEmpty()
{
	if (size == 0)
		return true;
	else
		return false;
}

template<class T>
bool Stack<T>::push(T item)
{
	state[size] = item;
	size++;
	return true;

}

template<class T>
bool Stack<T>::pop()
{
	bool success = !isEmpty();
	if (success)
	{
		state[size-1] = NULL;
		size--;
	}
	return success;
}

template<class T>
bool Stack<T>::pop(T& item)
{
	bool success = !isEmpty();
	if (success)
	{
		item = state[size-1];
		state[size-1] = NULL;
		size--;
	}
	return success;
}

template<class T>
inline T& Stack<T>::getTop()
{
	if (!isEmpty())
	{
		return state[size-1];
	}
	return state[0];
}

template<class T>
void Stack<T>::getTop(T& item)
{
	if (!isEmpty())
	{
		item = state[size-1];
	}
}

template<class T>
void Stack<T>::displayInOrder()
{
	if (!isEmpty())
	{
		for (int i = 0; i < size; i++)
		{
			cout << state[i] << endl;
		}
	}
}
