//#pragma once
//
//#include<string>
//#include<iostream>
//using namespace std;
//
//const int MAX_SIZE = 201;
//
//template<class K, class T>
//class Map
//{
//private:
//	struct Node
//	{
//		T item;	// data item
//		K key;
//		Node* left;	// pointer pointing to left subtree
//		Node* right;	// pointer pointing to right subtree
//	};
//
//	Node* items[MAX_SIZE];
//	int size;
//
//	void balanceTree(Node*& t);
//
//	// AVL Tree functions
//	Node* balance(Node* t)
//	{
//		int bal_factor = diff(t);
//
//		if (bal_factor > 1) 			// tree is left heavy
//		{
//			// cout << "Tree is left heavy -> do balancing" << endl;
//			if (diff(t->left) >= 0)		// left sub-tree is NOT right heavy
//				t = rotateRight(t);
//			else
//				t = rotateLeftRight(t);
//		}
//		else if (bal_factor < -1) 		// tree is right heavy
//		{
//			// cout << "Tree is right heavy -> do balancing" << endl;
//			if (diff(t->right) <= 0) 	// right sub-tree is NOT left heavy
//				t = rotateLeft(t);
//			else
//				t = rotateRightLeft(t);
//		}
//
//		return t;
//	}
//	Node* rotateLeft(Node* node)
//	{
//		// cout << "Rotate left" << endl;
//		Node* temp = node->right;
//		node->right = temp->left;
//		temp->left = node;
//		return temp;
//	}
//	Node* rotateRight(Node* node)
//	{
//		// cout << "Rotate right" << endl;
//		Node* temp = node->left;
//		node->left = temp->right;
//		temp->right = node;
//		return temp;
//	}
//	Node* rotateLeftRight(Node* node)
//	{
//		Node* temp = node->left;
//		node->left = rotateLeft(temp);
//		return rotateRight(node);
//	}
//	Node* rotateRightLeft(Node* node)
//	{
//		Node* temp = node->right;
//		node->right = rotateRight(temp);
//		return rotateLeft(node);
//	}
//	int diff(Node* t)
//	{
//		int l_height = getHeight(t->left);
//		int r_height = getHeight(t->right);
//		int b_factor = l_height - r_height;
//		return b_factor;
//	}
//	int getHeight(Node* t)
//	{
//		if (t == NULL)
//			return 0;
//		else
//		{
//			int leftHeight = getHeight(t->left);
//			int rightHeight = getHeight(t->right);
//			return 1 + max(leftHeight, rightHeight);
//		}
//	}
//
//public:
//	Map<K, T>();
//
//	~Map();
//
//	// Functions
//
//	// Inserting a key pair of {key, value}
//	bool insert(pair<K, T> pairarray[]);
//	bool insert(Node*& t, int hashKey, T value);
//
//	// Erasing based of the position of the iteration
//	bool erase(int iteratorpos);
//	bool erase(Node*& root, int iteratorpos);
//
//	// Erasing based of the key of the mapped value
//	bool erase(K key);
//	bool erase(Node*& t, K key);
//
//	// Searching the value of the mapped key with the key
//	T operator[](K key);
//	T search(Node* t, K Key);
//
//	// Hashing the key to get an integer for the comparison in key (AVL Tree)
//	int hash(K Key);
//
//	// Checking if the mapped AVL tree is empty
//	bool isEmpty();
//
//	// Counting the number of mapped values are in the map
//	int size();
//
//	// check if the AVL tree is balanced
//	int isBalanced();
//	bool isBalanced(Node* t);
//
//	// Iterators
//	T* begin() const;
//
//	T* end() const;
//
//	T* inorder();
//};
//
/////////////////////////////////
/////     IMPLEMENTATIONS     ///
////////////////////////////////
//
//// AVL Tree
//template<class K, class T>
//void Map<K, T>::balanceTree(Node*& t)
//{
//	if (t != NULL)
//	{
//		balanceTree(t->left);
//		balanceTree(t->right);
//		t = balance(t);			// AVL Tree function
//	}
//}
//
//// Constructor
//template<class K, class T>
//Map<K, T>::Map()
//{
//	size = 0;
//	for (int i = 0; i < MAX_SIZE; i++)
//	{
//		items[i] = NULL;
//	}
//}
//
//// Deconstructor
//template<class K, class T>
//Map<K, T>::~Map()
//{
//
//}
//
//// Insertion of the key and the value (helper function)
//template<class K, class T>
//bool Map<K, T>::insert(pair<K, T> pairarray[])
//{
//	// Converting the key to an integer if it is not an integer
//	int hashkey = this->hash(pairarray[0]);
//	Node* temp = new Node;
//	temp->item = newItem;
//	temp->key = newKey;
//	temp->next = NULL;
//	if (items[hashVal] != NULL)
//	{
//		Node* newTemp = items[hashVal];
//		if (newTemp->key == hashkey)
//		{
//			delete temp;
//			this->insert(newTemp, hashkey, pairarray[1]);
//		}
//		newTemp->next = temp;
//		newTemp = NULL;
//	}
//	else
//	{
//		items[hashVal] = temp;
//	}
//	size++;
//	
//}
//
//// Insertion of the key and the value (recursion function)
//template<class K, class T>
//bool Map<K, T>::insert(Node*& t, int hashKey, T value)
//{
//	// Inserting the key and and value into the map
//	if (t == NULL)
//	{
//		Node* newNode = new Node;
//		newNode->item = value;
//		newNode->key = hashKey;
//		newNode->left = NULL;
//		newNode->right = NULL;
//		t = newNode;
//	}
//	else if (hashKey < t->key)
//		insert(t->left, hashKey, value);  // insert in left subtree
//	else
//		insert(t->right, hashKey, value); // insert in right subtree	
//
//	t = balance(t);				// balance the tree (AVL Tree function)
//}
//
//// Erasing of mapped value with the key (Helper Function)
//template<class K, class T>
//bool Map<K, T>::erase(K key)
//{
//	int hashkey = hash(key);
//	if (items[hashkey] == key)
//	{
//		
//	}
//	else if ()
//	{
//		remove(items[hashkey], key);
//		balanceTree(root);
//	}
//
//}