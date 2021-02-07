// Queue.h - Specification of Queue ADT (Pointer-based)
#pragma once
#include<string>
#include<iostream>

using namespace std;

typedef sf::Vector2f ItemType;
const int max_size = 5;

class Queue
{
private:
	ItemType locations[max_size];
	string hashes[max_size];
	int size;
	int current;

public:
	// constructor
	Queue();

	~Queue();

	// enqueue (add) item at the front of queue
	bool enqueue_front(ItemType item);

	// enqueue (add) item at the front of queue
	bool enqueue_back(ItemType item);

	// dequeue (remove) item from front of queue
	bool dequeue_front();
	// dequeue (remove) and retrieve item from front of queue
	bool dequeue_front(ItemType& location, std::string& hash);

	// dequeue (remove) item from back of queue
	bool dequeue_back();
	// dequeue (remove) and retrieve item from back of queue
	bool dequeue_back(ItemType& location, std::string& hash);

	// retrieve (get) item from front of queue
	void getFront(ItemType& location, std::string& hash);

	// retrieve (get) item from back of queue
	void getBack(ItemType& location, std::string& hash);

	// check if the queue is empty
	bool isEmpty();

	// display items in queue from front to back
	// void displayItems();

	int getNoOfElements();
};