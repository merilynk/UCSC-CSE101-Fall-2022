// Filename: avl.cpp
// Contains the class AVL that represents an AVL self balancing tree. The file contains some of its basic operations.

#include "avl.h"
#include "node.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

AVL :: AVL()
{
	root = NULL;
}

int AVL :: get_bf(Node* n)
{
// 	if (n->left && n->right)
// 		return n->left->height - n->right->height;
// 	else if (n->left == NULL && n->right)
// 		return -(n->right->height);
// 	else if (n->left && n->right == NULL)
// 		return n->left->height;
// 	return 0;
	int balance_factor = 0;
	if (n->right)  // if a right child exists
		balance_factor += n->right->height;  // add the height of the right child
	if (n->left)  // if the left child exists
		balance_factor -= n->left->height;  // subtract the height of the left child
	return balance_factor;  // negative means it is left heavy, positive means right heavy
}

int AVL :: get_height(Node* n)
{
	if (n == NULL)
		return 0;
	if (n->left != NULL && n->right != NULL)
	{
		if (n->left->height > n->right->height)
			return n->left->height;
		else  // if (n->left->height <=  n->right->height)
			return n->right->height;
	}	
	else if (n->left != NULL && n->right == NULL)
		return n->left->height;
	else  // if (n->right != NULL && n->left == NULL)
		return n->right->height;
}

Node* AVL :: rotate_right(Node* n)
{
	if (n->left == NULL)
		return n;
	Node *n_parent = n->parent;
	Node *new_n = n->left;
	Node *temp = n->left->right;
	n->set_left(temp);
	new_n->set_right(n);
	new_n->parent = n_parent;
	return new_n;
}

Node* AVL :: rotate_left(Node* n)
{
	if (n->right == NULL)
		return n;
	Node *n_parent = n->parent;
	Node *new_n = n->right;
	Node *temp = n->right->left;
	n->set_right(temp);
	new_n->set_left(n);
	new_n->parent = n_parent;
	return new_n;
}

Node* AVL :: rotate_right_left(Node* n)
{
// 	Node *p_new = n->left->right;
// 	Node *p_left = n->left;
// 	Node *p_right = n;
	
// 	p_left->right = p_new->left;
// 	p_right->left = p_new->right;
// 	p_new->left = p_left;
// 	p_new->right = p_right;
// 	n = p_new;
	n->set_right(rotate_right(n->right));
	n = rotate_left(n);
 	return n;
}

Node* AVL :: rotate_left_right(Node* n)
{
// 	Node *p_new = n->right->left;
// 	Node *p_right = n->right;
// 	Node *p_left = n;
	
// 	p->left->right = p_new->left;
// 	p_right->left = p_new->right;
// 	p_new->left = p_left;
// 	p_new->right = p_right;
// 	n = p_new;
	n->set_left(rotate_left(n->left));
	n = rotate_right(n);
	return n;
}

void AVL :: insert(string s)
{
	Node *new_node = new Node(s);
	// cout << "Inserting " << s << endl;
	root = insert(root, new_node);
}

Node* AVL :: insert(Node* start, Node* to_insert)
{
	if (start == NULL)
		return to_insert;
	if (start-> data > to_insert->data)  // go left
	{
		start->set_left(insert(start->left, to_insert));
		if (get_bf(start) < -1)  // Left Heavy
		{
			if (start->left->data > to_insert->data)  // Left Right
				return rotate_left_right(start);
			else  // Right Right
				return rotate_right(start);  
		}
// 		if (get_bf(start) >= 2 && get_bf(start->left) >= 1)
// 			rotate_right(start);
// 		if (get_bf(start) >= 2 && get_bf(start->left) <= -1)
// 			rotate_left_right(start);
		start->left->parent = start;
		return start;
	}
	else if (start->data < to_insert->data)  // go right
	{
		start->set_right(insert(start->right, to_insert));
// 		if (get_bf(start) <= -2 && get_bf(start->right) <= -1)
// 			rotate_left(start);
// 		if (get_bf(start) <= -2 && get_bf(start->left) >= 1)
// 			rotate_right_left(start);
		if (get_bf(start) > 1)  // Right Heavy
		{
			if (start->right->data > to_insert->data)  // Right Left
				return rotate_right_left(start);
			else  // Left Left
				return rotate_left(start);
		}
		return start;
	}
	return start;  // duplicate value, no change needed
}

Node* AVL :: find(string d)
{
	return find(root, d);
}

Node* AVL :: find(Node* start, string d)
{
	if (start == NULL || start->data == d)
		return start;
	if (d < start->data)
		return find(start->left, d);
	else // if (d > start->data)
		return find(start->right, d);
}

int AVL :: count_before(Node* start, string end)
{
	if (start == NULL)
   return 0;
  if (start->data > end)
   return count_before(start->left, end);
  return 1 + (start->left ? start->left->size : 0) + count_before(start->right, end);
}

int AVL :: count_after(Node* start, string beginning)
{
	if (start == NULL)
		return 0;
	if (start->data < beginning)
    return count_after(start->right, beginning);
  return 1 + (start->right ? start->right->size : 0) + count_after(start->left, beginning);
}

int AVL :: range_query(string beginning, string end)
{
	return range_query(root, beginning, end);
}

int AVL :: range_query(Node* start, string beginning, string end)
{
	if (start == NULL)
		return 0;
	int self = (start->data == beginning || start->data == end) ? 1 : 0;
	if (start->data <= beginning)
		return self + range_query(start->right, beginning, end);
	else if (start->data >= end)
		return self + range_query(start->left, beginning, end);
	return 1 + count_before(start->right, end) + count_after(start->left, beginning);
}

void AVL :: print_in_order()
{
	print_in_order(root, 1);
}

void AVL :: print_in_order(Node* start, int level)
{
	if (start == NULL)
		return;
	print_in_order(start->left, level + 1);
	cout << level << ": " << start->data << " , size: " << start->size << endl;
	print_in_order(start->right, level + 1);
}