#pragma once

#include<string>
#include<iostream>
using namespace std;

const int maximum_size = 201;

template<class K, class T>
class Map
{
private:
	struct Node
	{
		K  key;   // search key
		T item;	// data item
		Node* next;	// pointer pointing to next item
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
	for (int i = 0; i < 201; i++)
	{
		items[i] = nullptr;
	}
}

// Deconstructor
template<class K, class T>
Map<K, T>::~Map()
{
	for (int i = 0; i < 201; i++)
	{
		if (items[i] != nullptr)
		{
			delete items[i];
			items[i] = nullptr;
		}
	}
	size = 0;
}

// Insertion of the key and the value
template<class K, class T>
bool Map<K, T>::insert(pair<K, T> pairarray[])
{
	// Converting the key to an integer if it is not an integer
	int hashkey = this->hash((std::string)pairarray[0]);
	Node* temp = new Node;
	temp->item = (T)pairarray[1];
	temp->key = (K)pairarray[0];
	temp->next = nullptr;
	if (items[hashkey] != nullptr)
	{
		Node* newTemp = items[hashkey];
		// Checks if the first Actual Key are the same 
		if (newTemp->key == pairarray[0])
		{
			return false;
		}
		// Iterates over until it reaches the last of the linked list
		while (newTemp->key != NULL)
		{
			if (newTemp->key == pairarray[0])
				return false;
			newTemp = newTemp->next;
		}
		newTemp->next = temp;
		newTemp = NULL;
	}
	else
	{
		items[hashkey] = temp;
	}
	size++;
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
		Node* newTemp = items[hashkey];
		Node* temp = nullptr;
		// iterates over to get the node with the same key and the one previous
		while(newTemp->key != nullptr)
		{
			if (newTemp->next != nullptr)
			{
				temp = newTemp;
				newTemp = newTemp->next;
			}
			else
				break;
		}
		if (newTemp->key == Key)
		{
			// when there is only one
			if (temp == nullptr)
			{
				items[hashkey] = nullptr;
				delete newTemp;
			}
			else
			{
				// when there is multiple and the node is between two nodes
				if (newTemp->next != nullptr)
				{
					temp->next = newTemp->next;
				}
				// when there is multiple and the node is at the last
				else
				{
					temp->next = nullptr;
				}
				delete newTemp;
			}
		}
		else
		{
			return false;
			// cout << "No item found with the key " << key << endl;
		}
		size--;
		temp = NULL;
		newTemp = NULL;
		return success;
		
	}
}

// Searching with the key
template<class K, class T>
T Map<K, T>::operator[] (K Key)
{
	int hashKey = this->hash(Key);
	if (items[hashKey] != nullptr)
	{
		Node* newTemp = items[hashKey];
		// Iterates if it is not the key
		while (newTemp->key != Key)
		{
			if (newTemp->next != NULL)
			{
				newTemp = newTemp->next;
			}
		}
		// Return if it is the key
		if (newTemp->key == Key)
			return newTemp->item;
		else
			return T();
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
		Node* newTemp = items[hashKey];
		// Iterates if it is not the key
		while (newTemp->key != Key)
		{
			if (newTemp->next != NULL)
			{
				newTemp = newTemp->next;
			}
		}
		// Return if it is the key
		if (newTemp->key == Key)
			return newTemp->item;
		else
			return T();
	}
	else
		return T();
}

template<class K, class T>
inline bool Map<K, T>::Change(pair<K, T> pairarray[])
{
	int hashKey = this->hash(pairarray[0]);
	if (items[hashKey] != nullptr)
	{
		Node* newTemp = items[hashKey];
		// Iterates if it is not the key
		while (newTemp->key != pairarray[0])
		{
			if (newTemp->next != NULL)
			{
				newTemp = newTemp->next;
			}
		}
		// Return if it is the key
		if (newTemp->key == pairarray[0])
		{
			newTemp->item = pairarray[1];
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

template<class K, class T>
int Map<K, T>::hash(std::string Key)
{
	unsigned hk = salt;
	for (int i = 0; i < Key.size(); i++)
		hk = (hk * maximum_size + (unsigned)Key[i]) % maximum_size;
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

