// Filename: linkedlist.cpp

// Contains the class LinkedList that represents a linked list. This contains some basic operations, such as insert, delete, find, and length.

#include "linkedlist.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Linked List contructor
LinkedList :: LinkedList() 
{
		head = NULL;
}

void LinkedList :: insert(string str) 
{
		Node *to_add = new Node;
		to_add->word = str;
		to_add->freq = 1;
  
		to_add->next = head;
		head = to_add;
}

Node* LinkedList :: find(string str) 
{
		Node *curr = head;
  
		while (curr != NULL) 
		{
    
			if (curr->word == str)  
			{
					return curr;
			}
    
			curr = curr->next;
		}
  
		return NULL;
}

Node* LinkedList :: getHead()
{
	return head;
}

Node* LinkedList :: deleteNode(string str) 
{
		Node *prev = NULL;
		Node *curr = head;
		while (curr != NULL) 
		{
    
			if (curr->word == str) 
			{
					break;
			}
    
			prev = curr;
			curr = curr->next;
		}
  
		if (curr == NULL) 
		{
				head = head->next;
		}
		else 
		{
				prev->next = curr->next;
		}
	
		curr->next = NULL;
		return curr;
}

void LinkedList :: deleteAndFreeNode(string str) 
{
	
		Node* ptr = deleteNode(str);
		if (ptr != NULL) 
		{
				ptr->next = NULL;
				delete(ptr);
		}
	
		return;
}

void LinkedList :: deleteList() 
{
		Node *curr = head;
		Node *temp = NULL;
	
		while (curr != NULL) 
		{
				temp = curr->next;
				delete(curr);
				curr = temp;
		}
		head = NULL;
}

string LinkedList :: print() 
{
		string list_str = "";
		Node *curr = head;
	
		if (head == NULL) 
		{
				return "Empty LL.";
		}
	
		while (curr != NULL) 
		{
				list_str = list_str + curr->word + ": " + to_string(curr->freq) + " | ";
				curr = curr->next;
		}
		
		if (list_str.length() > 0) 
		{
				list_str.pop_back();
		}
		return list_str;
}

int LinkedList :: length() 
{
		int length = 0;
		Node *curr = head;
		
		while (curr != NULL) 
		{
				length ++;
				curr = curr->next;
		}
		return length;
}

