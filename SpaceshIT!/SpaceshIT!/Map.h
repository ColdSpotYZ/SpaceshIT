#pragma once

#include<string>
#include<iostream>
using namespace std;

#include "BinaryNode.h"
#include "AVL_Tree.h"	

template<class T, class V>
class Map
{
	private:
		BinaryNode* root;

	public:
		Map<T, V>();

		~Map();
		
		// Functions

		// Inserting a key pair of {key, value}
		bool insert(pair<T, V> pairarray[]);
		bool insert(BinaryNode*& t, pair<T, V> pairarray[]);

		// Erasing based of the position of the iteration
		bool erase(int iteratorpos);
		bool erase(BinaryNode*& root, int iteratorpos);

		// Erasing based of the key of the mapped value
		bool erase(T key);
		bool erase(BinaryNode*& root, T key);
		
		// Searching the value of the mapped key with the key
		V search(T key);
		V search(BinaryNode* root, T key);

		// Hashing the key to get an integer for the comparison in key (AVL Tree)
		int hash(T Key);

		typename V::iterator begin();

		typename V::iterator end();

		// Checking if the mapped AVL tree is empty
		bool isEmpty();

		// Counting the number of mapped values are in the map
		int size();

		// computing the height of the AVL tree of the map
		int getHeight();

		// check if the AVL tree is balanced
		int isBalanced();

};

///////////////////////////////
///     IMPLEMENTATIONS     ///
//////////////////////////////

template<class T, class V>
Map<T, V>::Map<T, V>()
{
	root = NULL;
}

template<class T, class V>
Map<T, V>::~Map()
{
	

}

template<class T, class V>
bool Map<T, V>::insert(pair<T, V> pairarray[])
{
	// Converting the key to an integer if it is not an integer
	if (!(T is int))
	{
		int hashkey = this->hash(pairarray[1])
	}

	pairarray[0] = hashkey;
	this->insert(root, pairarray)
}

template<class T, class V>
bool Map<T, V>::insert(BinaryNode*& t, pair<T, V> pairarray[])
{
	// Inserting the key and and value into the map
	if (t == NULL)
	{
		BinaryNode* newNode = new BinaryNode;
		newNode->item = pairarray[0];
		newNode->key = hashkey
		newNode->left = NULL;
		newNode->right = NULL;
		t = newNode;
	}
	else if (pairarray[0] < t->item)
		insert(t->left, item);  // insert in left subtree
	else
		insert(t->right, item); // insert in right subtree	

	t = balance(t);				// balance the tree (AVL Tree function)
}

template<class T, class V>
bool Map<T, V>::erase(int iteratorpos)
{

}

template<class T, class V>
bool Map<T, V>::erase(T key)
{

}

template<class T, class V>
V Map<T, V>::search(T key)
{

}

template<class T, class V>
int Map<T, V>::hash(T key)
{
	return 0;
}

template<class T, class V>
typename V::iterator Map<T, V>::begin()
{
	return this->root;
}

template<class T, class V>
typename V::iterator Map<T, V>::end()
{
	return this->root + this->size;
}



template<class T, class V>
bool Map<T, V>::isEmpty()
{
	if (size == 0)
		return true;
	else
		return false;
}

template<class T, class V>
int Map<T, V>::size()
{
	return size;
}

template<class T, class V>
int Map<T, V>::getHeight()
{

}

template<class T, class V>
int Map<T, V>::isBalanced()
{

}