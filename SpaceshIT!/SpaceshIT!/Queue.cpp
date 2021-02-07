#pragma once
#include "stdafx.h"
#include "Queue.h"
#include <string>
#include "sha256.h"

using namespace std;

Queue::Queue() { size = 0; current = 0; salt = rand() % 512;}

Queue::~Queue()
{
	while (!isEmpty())
	{
		dequeue_back();
	}
	current = NULL;
	size = NULL;
}

bool Queue::enqueue_back(ItemType item)
{
	if (size >= 4)
	{
		dequeue_front();
	}
	string hashoflocation = xhash((std::to_string(item.x) + std::to_string(item.y)));
	locations[current] = item;
	hashes[current] = hashoflocation;
	size++;
	current++;
	current = current % 5;
	return true;
}

bool Queue::enqueue_front(ItemType item)
{
	if (size >= 4)
	{
		dequeue_back();
	}
	string hashoflocation = xhash((std::to_string(item.x) + std::to_string(item.y)));
	locations[current] = item;
	hashes[current] = hashoflocation;
	size++;
	current--;
	current = current % 5;
	return true;
}

bool Queue::dequeue_back()
{
	bool success = !isEmpty();
	if (success)
	{
		current++;
		current = current % 5;
		locations[current].x = NULL;
		locations[current].y = NULL;
		hashes[current] = "";
		size--;
	}
	return success;
}

bool Queue::dequeue_back(ItemType& location, std::string& hash)
{
	bool success = !isEmpty();
	if (success)
	{
		current++;
		current = current % 5;
		location = locations[current];
		hash = hashes[current];
		locations[current].x = NULL;
		locations[current].y = NULL;
		hashes[current] = "";
		size--;
	}
	return success;
}

bool Queue::dequeue_front()
{
	bool success = !isEmpty();
	if (success)
	{
		current--;
		current = current % 5;
		locations[current].x = NULL;
		locations[current].y = NULL;
		hashes[current] = "";
		size--;
	}
	return success;
}

bool Queue::dequeue_front(ItemType& location, std::string& hash)
{
	bool success = !isEmpty();
	if (success)
	{
		current--;
		current = current % 5;
		location = locations[current];
		hash = hashes[current];
		locations[current].x = NULL;
		locations[current].y = NULL;
		hashes[current] = "";
		size--;
	}
	return success;
}

void Queue::getFront(ItemType& location, std::string& hash)
{
	if (!isEmpty())
	{
		if (size == 5) // When the array is full the front of the queue would be the next of the current
		{
			location = locations[current + 1];
			hash = hashes[current + 1];
		}
		else
		{
			location = locations[current - size];
			hash = hashes[current - size];
		}
	}
}

void Queue::getBack(ItemType& location, std::string& hash)
{
	if (!isEmpty())
	{
		int temp = current - 1;
		temp = temp % 5;
		location = locations[temp];
		hash = hashes[temp];
	}
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