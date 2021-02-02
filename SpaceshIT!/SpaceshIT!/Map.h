#pragma once

#include<string>
#include<iostream>

typedef std::string ItemType;
const int MAX_SIZE = 10;

class Map
{
	private:
		struct Node
		{
			int key;
			ItemType value;
			Node* next;
			Node* prev;
		};

		Node* TopNode;

	public:
		Map();

		~Map();
};

