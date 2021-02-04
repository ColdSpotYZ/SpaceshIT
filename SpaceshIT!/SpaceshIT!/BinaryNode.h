#pragma once

typedef string ItemType;

struct BinaryNode
{
	ItemType   item;	// data item
	int key;
	BinaryNode* left;	// pointer pointing to left subtree
	BinaryNode* right;	// pointer pointing to right subtree
};