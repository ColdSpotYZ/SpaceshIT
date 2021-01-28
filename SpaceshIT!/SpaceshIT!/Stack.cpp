#include "Stack.h"


Stack::Stack() { topNode = NULL; };

Stack::~Stack()
{
	while (!isEmpty())
	{
		pop();
	}

}

bool Stack::isEmpty()
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

bool Stack::push(ItemType& item)
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

bool Stack::pop()
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

bool Stack::pop(ItemType& item)
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

void Stack::getTop(ItemType& item)
{
	if (!isEmpty())
	{
		item = topNode->item;
	}
}

void Stack::displayInOrder()
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

void Stack::displayInOrderOfInsertion()
{
	ItemType item;
	Stack tempStack;
	if (!isEmpty())
	{
		while (!isEmpty())
		{
			getTop(item);
			tempStack.push(item);
			pop();
		}

		while (!tempStack.isEmpty())
		{
			tempStack.getTop(item);
			cout << item << endl;
			push(item);
			tempStack.pop();
		}
	}
}