// Queue.h - Specification of Queue ADT (Pointer-based)
#pragma once
#include<string>
#include<iostream>
#include "Vector.h"

using namespace std;

typedef string ItemType;

const int MAX_SIZE = 5;

class Queue
{
private:
	ItemType location[MAX_SIZE];
	string hash[MAX_SIZE];
	int size;
	int current;

public:
	// constructor
	Queue();

	~Queue();

	// enqueue (add) item at the back of queue
	bool enqueue(string item);

	// dequeue (remove) item from front of queue
	bool dequeue();

	// dequeue (remove) and retrieve item from front of queue
	bool dequeue(ItemType& item);

	// retrieve (get) item from front of queue
	void getFront(ItemType& item);

	// check if the queue is empty
	bool isEmpty();

	// display items in queue from front to back
	void displayItems();

	bool getLastElement(Queue& q, ItemType& item);

	int getNoOfElements();
};
