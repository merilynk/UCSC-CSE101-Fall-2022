// Filename: node.h
// Header file for the Node class.

#include <algorithm>
#include <string>
using namespace std;

#ifndef NODE_H
#define NODE_H

class Node
{
	public:
		string data;
		Node *left;
		Node *right;
		int height;
		int size;
		Node *parent;
		Node(string d)
		{
			this->data = d;
			this->left = NULL;
			this->right = NULL;
			this->height = 1;
			this->size = 1;
			this->parent = NULL;
		}
		Node(string d, Node* l, Node* r)
		{
			this->data = d;
			this->right = r;
			this->left = l;
			this->height = 1;
			this->size = 1;
			if (l)
			{
				this->height = max(this->height, l->height + 1);
				this->size += l->size;
			}
			if (r)
			{
				this->height = max(this->height, r->height + 1);
				this->size += r->size;
			}
			this->parent = NULL;
		}
		Node* set_left(Node *new_left)
		{
			this->left = new_left;
			this->height = 1;
			this->size = 1;
			if (this->left)
			{
				this->height = max(this->height, left->height + 1);
				this->size += left->size;
			}
			if (this->right)
			{
				this->height = max(this->height, right->height + 1);
				this->size += right->size;
			}
			return this;
		}
		Node* set_right(Node *new_right)
		{
			this->right = new_right;
			this->height = 1;
			this->size = 1;
			if (this->left)
			{
				this->height = max(this->height, left->height + 1);
				this->size += left->size;
			}
			if (this->right)
			{
				this->height = max(this->height, right->height + 1);
				this->size += right->size;
			}
			return this;
		}
};

#endif //NODE_H