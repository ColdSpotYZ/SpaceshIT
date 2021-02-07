#pragma once

#include<string>
#include<iostream>
using namespace std;

const int maximum_size = 1001;

template<class K, class T>
class Map
{
private:
	struct Node
	{
		K  key;   // search key
		T item;	// data item
		Node* next;
	};

	Node* items[maximum_size];
	int size;
	unsigned salt;

public:

	Map<K, T>();

	~Map();

	// Functions

	// Inserting a key pair of {key, value}
	bool insert(pair<K, T> pairarray[]);

	// Hashing the key to get an integer for the comparison in key (AVL Tree)
	int hash(std::string Key);

	// Erasing based of the position of the iteration
	bool erase(int iteratorpos);
	bool erase(Node*& root, int iteratorpos);

	// Erasing based of the key of the mapped value
	bool erase(K key);

	// Accessors through keys
	T operator[](K key);
	T at(K Key);

	// Modification of Keys
	bool Change(pair<K, T> pairarray[]);

	// Checking if the mapped AVL tree is empty
	bool isEmpty();

	// Counting the number of mapped values are in the map
	int getAmount();

	// Prints out all the mapping of the key to the value
	void printMap();
};

///////////////////////////////
///     IMPLEMENTATIONS     ///
//////////////////////////////

// Constructor
template<class K, class T>
Map<K, T>::Map()
{
	size = 0;
	salt = rand() % maximum_size;
	for (int i = 0; i < maximum_size; i++)
	{
		items[i] = nullptr;
	}
}

// Deconstructor
template<class K, class T>
Map<K, T>::~Map()
{
	size = 0;
	for (int i = 0; i < maximum_size; i++)
	{
		items[i] = nullptr;
	}
}

// Insertion of the key and the value
template<class K, class T>
bool Map<K, T>::insert(pair<K, T> pairarray[])
{
	// Converting the key to an integer if it is not an integer
	int hashkey = this->hash((std::string)pairarray->first);
	// cout << hashkey << endl;
	Node* temp = new Node;
	temp->item = (T)pairarray->second;
	temp->key = (K)pairarray->first;
	if (items[hashkey] != nullptr)
	{
		return false;
	}
	else
	{
		items[hashkey] = temp;
	}
	size++;
	printMap();
	return true;
}

// Erasing of mapped value with the key
template<class K, class T>
bool Map<K, T>::erase(K Key)
{
	bool success = true;
	int hashkey = hash(Key);
	if (items[hashkey] != nullptr)
	{
		delete items[hashkey];
		size--;
		return true;
	}
	else
	{
		return false;
	}
}

// Searching with the key
template<class K, class T>
T Map<K, T>::operator[] (K Key)
{
	int hashKey = this->hash(Key);
	if (items[hashKey] != nullptr)
	{
		return items[hashKey]->item;
	}
	else
		return T();
}

template<class K, class T>
inline T Map<K, T>::at(K Key)
{
	int hashKey = this->hash(Key);
	if (items[hashKey] != nullptr)
	{
		return items[hashKey]->item;
	}
	else
		return T();
}

template<class K, class T>
inline bool Map<K, T>::Change(pair<K, T> pairarray[])
{
	int hashKey = this->hash((K)pairarray->first);
	if (items[hashKey] != nullptr)
	{
		items[hashKey]->item = (T)pairarray->second;
	}
	else
		return false;
}

template<class K, class T>
int Map<K, T>::hash(std::string Key)
{
	unsigned hk = salt;
	for (int i = 0; i < Key.size(); i++)
		hk = (hk * 101 + (unsigned)Key[i]) % maximum_size;
	return hk;
}

template<class T, class V>
bool Map<T, V>::isEmpty()
{
	if (getAmount() == 0)
		return true;
	else
		return false;
}

template<class T, class V>
int Map<T, V>::getAmount()
{
	return size;
}

template<class K, class T>
inline void Map<K, T>::printMap()
{
	for (int i = 0; i < maximum_size; i++)
	{
		if (items[i] != nullptr)
		{
			// cout << "valid" << endl;
		}
	}
}

