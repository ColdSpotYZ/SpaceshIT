#include "Queue.h"
#include <string>

using namespace std;

Queue::Queue() { frontNode = NULL; backNode = NULL; }

Queue::~Queue()
{
	while (!isEmpty())
	{
		dequeue();
	}
}

bool Queue::enqueue(ItemType item)
{
	Node* temp = new Node;
	temp->location = item;
	temp->next = NULL;
	if (!isEmpty())
	{
		backNode->next = temp;
		backNode = temp;
	}
	else
	{
		frontNode = temp;
		backNode = temp;
	}
	temp = NULL;
	return true;
}

bool Queue::dequeue()
{
	bool success = !isEmpty();
	if (success)
	{
		if (frontNode->next == NULL)
		{
			delete frontNode;
			frontNode = NULL;
			backNode = NULL;
		}
		else
		{
			Node* temp = new Node;
			temp = frontNode;
			frontNode = temp->next;
			delete temp;
			temp = NULL;
		}
	}
	return success;
}

bool Queue::dequeue(ItemType &item)
{
	bool success = !isEmpty();
	if (success)
	{
		item = frontNode->location;
		if (frontNode->next == NULL)
		{
			delete frontNode;
			frontNode = NULL;
			backNode = NULL;
		}
		else
		{
			Node* temp = new Node;
			temp = frontNode;
			frontNode = temp->next;
			delete temp;
			temp = NULL;
		}
	}
	return success;
}

void Queue::getFront(ItemType& item)
{
	item = frontNode->location;
}

bool Queue::isEmpty()
{
	if (frontNode == NULL)
		return true;
	else
		return false;
}

void Queue::displayItems()
{
	if (!isEmpty())
	{
		Node* temp = new Node;
		temp = frontNode;
		cout << "=== Displaying items in the Queue ===" << endl;
		while (temp != backNode)
		{
			cout << temp->location << endl;
			temp = temp->next;
		}
		cout << backNode->location << endl;
		temp = NULL;
	}
	else
	{
		cout << "Queue is Empty" << endl;
	}

}


bool Queue::getLastElement(Queue& q, ItemType& item)
{
	bool success = !q.isEmpty();
	if (success)
	{
		Queue newQ = q;
		while (!newQ.isEmpty())
		{
			newQ.dequeue(item);
		}
	}
	return success;
}

int Queue::getNoOfElements()
{
	bool success = !isEmpty();
	int count = 0;
	Queue tempQueue;
	ItemType itemtype;
	if (success)
	{
		while (!isEmpty())
		{
			dequeue(itemtype);
			tempQueue.enqueue(itemtype);
			count++;
		}

		while (!tempQueue.isEmpty())
		{
			tempQueue.dequeue(itemtype);
			enqueue(itemtype);
		}
		return count;
	}
	else
	{
		return 0;
	}
}