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
		
		// 
		bool insert(pair<T, V> pairarray[]);

		bool erase(int interatorpos);

		bool erase(V key);

		T search(V key);

		typename T::iterator begin();

		typename T::iterator end();

		bool isEmpty();

		int size();

		int getHeight();

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
	if (!(V is int))
	{

	}
}

template<class T, class V>
bool Map<T, V>::erase(int interatorpos)
{

}

template<class T, class V>
bool Map<T, V>::erase(V key)
{

}

template<class T, class V>
T Map<T, V>::search(V key)
{

}

template<class T, class V>
typename T::iterator Map<T, V>::begin()
{
	return this->root;
}

template<class T, class V>
typename T::iterator Map<T, V>::end()
{
	return this->root + this->size;
}



template<class T, class V>
bool Map<T, V>::isEmpty()
{

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