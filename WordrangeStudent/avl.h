// Filename: avl.h
// Header file for the range queries AVL tree.

#include "node.h"

class AVL
{
	private:
		Node *root;
		int get_bf(Node*);  // gets the balance factor of the tree
		int get_height(Node*);  // gets the height of the node
		Node* rotate_left(Node*);
		Node* rotate_right(Node*);
		Node* rotate_left_right(Node*);
		Node* rotate_right_left(Node*);
	public:
		AVL();  // constructor
		void insert(string);  // insert wrapper function
		Node* insert(Node*, Node*);  // inserts a node into tree
		Node* find(string);  // find a string in tree and return the node with that string
		Node* find(Node*, string);  // recursive function that finds in a string subtree
		int count_before(Node*, string);
		int count_after(Node*, string);
		int range_query(string, string);  // wrapper function for range querying
		int range_query(Node*, string, string);  // recursive function for finding the number of words between the range
		void print_in_order();  // print wrapper function
		void print_in_order(Node*, int);  // recursive function for printing the tree in order
};