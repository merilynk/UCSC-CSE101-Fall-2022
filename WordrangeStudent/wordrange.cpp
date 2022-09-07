// Filename: wordrange.cpp

#include "node.h"
#include "avl.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 3)  // check for correct usage with 3 arguments
		throw std::invalid_argument("Usage: ./wordrange <INPUT FILE> <OUTPUT FILE>");
	
	ifstream infile;  // input file stream
	ofstream outfile;  // output file stream
	
	infile.open(argv[1]);  // open input file
	outfile.open(argv[2]);  // open output file
	
	string line; // to store the next line, either "i" or "r"
	char *command, *valstr, *operation;  // for using with strtok()
	string word_val;  // the value from the line from the input
	string word_val2;  // the second value from the line if necessary
	
	AVL myAVL;  // initializing the self balancing binary search tree
	
	while (getline(infile, line))  // get the next line of input, store the line contents
	{
		if (line.length() == 0)  // if the line was empty, go to next line
			continue; 
		command = strdup(line.c_str());  // copy the string into a C-style string
		operation = strtok(command, " \t");  // tokenize line on whitespace, first token is the operation
		
		valstr = strtok(NULL, " \t");  // the second token is a string value
		if (valstr != NULL)
			word_val = valstr;
		
		valstr = strtok(NULL, " \t");  // there may be a third token that is also a string value
		if (valstr != NULL)
			word_val2 = valstr;
		
		if (strcmp(operation, "i") == 0)
		{
			// cout << "Insert " + word_val << endl;
			myAVL.insert(word_val);
		}
		if (strcmp(operation, "r") == 0)
		{
			// cout << "Range query "  + word_val + " to " + word_val2 << endl;
			outfile << myAVL.range_query(word_val, word_val2) << endl;
		}
	}
	
	infile.close();  // close input file
	outfile.close();  // close output file
	
	return 0;
	
}