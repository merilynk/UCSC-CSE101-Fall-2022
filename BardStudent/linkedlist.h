// Filename: linkedlist.h

// Header file fo the class LinkedList.

#ifndef LIST_H
#define LIST_H

#include <string>

using namespace std;

// node struct to hold data
struct Node 
{
  int freq;
	string word;
  Node *next;
};

class LinkedList 
{ 
  private:
    Node *head; // Stores head of linked list
  public:
    LinkedList(); 
    void insert(string);
    Node* find(string);
		Node* getHead();
    Node* deleteNode(string);
		void deleteAndFreeNode(string);
    void deleteList();
    string print();
    int length();
};

#endif
