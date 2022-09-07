// Filename: bard.cpp

// This is the main function that performs word analysis of Shakesphere's works.
// 36 letters is the longest length.
#define DEBUG

#include <iostream>
#include "linkedlist.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;

int findLongestWord (string fileName)
{
		ifstream file;
		file.open(fileName);
		string word;
		int longest = 0;
		while(getline(file, word))  // shakespeareFile.good()
		{
				int wordLen = word.length();
				if (wordLen > longest)
				{
						longest = wordLen;
				}
		}
		file.close();
		return longest;
}

int main(int argc, char** argv) 
{
		// Make sure valid arguments were entered into the command line.
		if (argc < 3)
		{
				throw std :: invalid_argument("Usage: ./bard <INPUT FILE> <OUTPUT FILE>");
		}
	
#ifdef DEBUG
		cout << "Opening Shakepeare file...";
#endif
		ifstream shakespeareFile;  // stream for Shakespeare file
		shakespeareFile.open("shakespeare-cleaned5.txt");  // open Shakespeare file
#ifdef DEBUG
	cout << "Done." << endl;
#endif
		
	
	  // Initalize an array of linked lists to store the words. 
#ifdef DEBUG
	cout << "Initializing array of linked lists ...";
	
#endif
		LinkedList* arrayOfLL = new LinkedList[findLongestWord("shakespeare-cleaned5.txt") + 1];  // The index of the array is the length of the words stored in the linked lists there.
#ifdef DEBUG
	cout << "Done" << endl;
#endif
		
		
		// Parse through each line of Shakespeare text to get each word.
#ifdef DEBUG
	cout << "Parsing shakespeare file..." << endl;
#endif
		string word;  // to store the words from each line of Shakespeare file
		
		while(getline(shakespeareFile, word))  // shakespeareFile.good()
		{
				int wordLen = word.length(); 
				//arrayOfLL[wordLen].insert(word);  // Add the word to the linked list	

// #ifdef DEBUG
//  		cout << "Checking for " + word + "...";
// #endif
				Node *found = arrayOfLL[wordLen].find(word);  // find the word
				
				// Check if the word is found
				if (found == NULL)
				{
						//cout << "NOT FOUND...";
						arrayOfLL[wordLen].insert(word);  // Add the word to the linked list	
						//cout << "NOW ADDED...";
				}					
				else
				{
						//cout << "FOUND...";
						found->freq ++;  // Increase the frequency of the word
						//cout << to_string(found->freq) + "...";
				}
// #ifdef DEBUG
//  			cout << "Done." << endl;
// #endif
		}
#ifdef DEBUG
	cout << "Done." << endl;
	//cout << "Removing duplicate words...";
	
// 	for (int i = 5; i < 37; i++)
// 	{
// 			cout << arrayOfLL[i].print() << endl;
// 	}
#endif
	
#ifdef DEBUG
	cout << "Sorting through linked lists...";
#endif 
		// Loop through each linked list in the array.
		for (int i = 5; i < 37; i++)
		{
				Node *max = arrayOfLL[i].getHead();  // will store the node with the highest frequency
				Node *current = arrayOfLL[i].getHead();  // current node pointer
				Node *ptr = arrayOfLL[i].getHead();  // used to iterate through linked lists
								
				// Sort the linked list (selection sort).
				string temp_word = "";  // temp values used for swapping
				int temp_freq = 0;
			
				while (current != NULL)
				{
						while (ptr->next != NULL)
						{
								ptr = ptr->next;
								if (ptr->freq > max->freq)
								{
									max = ptr;
								}
								if (ptr->freq == max->freq)
								{
										if (ptr->word < max->word)
										{
											max = ptr;
										}
								}
						}
						
						// Swap the data in the nodes.
						temp_word = max->word;
						temp_freq = max->freq;
						max->word = current->word;
						max->freq = current->freq;
						current->word = temp_word;
						current->freq = temp_freq;
					
						current = current->next;  // move to next node in linked list
						max = current;  // reset max to current
						ptr = current;  // reset ptr to current
				}				
		}
#ifdef DEBUG
	cout << "Done." << endl;
#endif
	
		ifstream infile;  // input file stream
		ofstream outfile;  // output file stream
	
		infile.open(argv[1]);  // open input file
		outfile.open(argv[2]);  // open output file
	
		string query;  // to store the next query
		char *qry;  // for use with sscanf
		int word_len, rank;  // values from the query

#ifdef DEBUG
	cout << "Querying...";
#endif
		// Parse input file from command line.
		while (getline(infile, query)) 
		{
				if (query.length() == 0)  // check if command is empty
				{
						continue;
				}
				qry = strdup(query.c_str());  // copy string into a char
				sscanf(qry, "%d %d", &word_len, &rank);
			
				LinkedList ll = arrayOfLL[word_len];  // get linked list storing the words of the word length
				//cout << ll.print() << endl;
				Node *current = ll.getHead();  // get head of linked list
				
				// Check if invalid word length
				if (word_len < 5 || word_len > 36) 
				{
						cout << "-" << endl;
						outfile << "-" << endl;
						continue;
				}
				
				// Check if invalid rank.
				if (rank >= ll.length())
				{
						cout << "-" << endl;
						outfile << "-" << endl;
						continue;
				}
			
				for (int f = 0; f < rank; f++)
				{
						current = current->next;
				}
				
				cout << current->word << endl;
				outfile << current->word << endl;
		}
	
#ifdef DEBUG
	cout << "Done." << endl;
	cout << "Deleting linked lists...";
#endif	
	
		for (int i = 0; i < 37; i++)
		{
			arrayOfLL[i].deleteList();
		}
	
#ifdef DEBUG
	cout << "Done." << endl;
	cout << "Closing files...";
#endif
		shakespeareFile.close();  // close Shakespeare file
		infile.close();
		outfile.close();
#ifdef DEBUG
	cout << "Done." << endl;
#endif	
}