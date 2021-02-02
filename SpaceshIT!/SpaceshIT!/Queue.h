// Queue.h - Specification of Queue ADT (Pointer-based)
#pragma once
#include<string>
#include<iostream>


using namespace std;

typedef string ItemType;

const int MAX_SIZE = 4;

class Queue
{
private:
	ItemType locations[MAX_SIZE];
	string hashes[MAX_SIZE];
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
	bool dequeue(ItemType& location, ItemType hash);

	// retrieve (get) item from front of queue
	void getFront(ItemType& location, ItemType hash);

	// check if the queue is empty
	bool isEmpty();

	// display items in queue from front to back
	// void displayItems();

	int getNoOfElements();
};