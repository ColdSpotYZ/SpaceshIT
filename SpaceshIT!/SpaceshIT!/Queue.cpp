#include "stdafx.h"
#include "Queue.h"
#include <string>
#include "sha256.h"

using namespace std;

Queue::Queue() { size = 0; current = 0; }

Queue::~Queue()
{
	while (!isEmpty())
	{
		dequeue();
	}
	current = NULL;
	size = NULL;
}

bool Queue::enqueue(ItemType item)
{

	if (size == 5)
	{
		dequeue();
	}
	string hashoflocation = sha256(item);
	locations[current] = item;
	hashes[current] = hashoflocation;
	size++;
	current = (current++) % 4;
	return true;
}

bool Queue::dequeue()
{
	bool success = !isEmpty();
	if (success)
	{
		locations[current].clear();
		hashes[current].clear();
	}
	return success;
}

bool Queue::dequeue(ItemType& location, ItemType hash)
{

	bool success = !isEmpty();
	if (success)
	{
		if (size == 0)
			current = 4;
		else if (size != 5)
		{
			current = (current--) % 4;
		}
		location = location[current];
		hash = hash[current];
		locations[current].clear();
		hashes[current].clear();
	}
	return success;
}

void Queue::getFront(ItemType& location, ItemType hash)
{
	location = location[current];
	hash = hash[current];
}

bool Queue::isEmpty()
{
	if (size == 0)
		return true;
	else
		return false;
}

int Queue::getNoOfElements()
{
	return size;
}