// Filename: nqueens.cpp

#include "chessboard.h"
#include "queen.h"
#include <iostream>
#include <stack>
#include <stdexcept>
#include <fstream> 
#include <array>
#include <vector>
#include <string> 
#include <cstring>
#include <algorithm>
#include <list>
#include <stdlib.h>
#include <sstream>
using namespace std; 

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		throw std::invalid_argument("Usage: ./nqueens <INPUT FILE> <OUTPUT FILE>");
	}
	
	ifstream infile;  // stream for input file
	ofstream outfile;  // stream for output file
	
	infile.open(argv[1]);   // open input file
	outfile.open(argv[2]);  // open output file
	
	string instance;  // to store the next instance in the input file
	
	// Parse input file.
	while (getline(infile, instance))
	{
		//int len = instance.length();  // get length of the string
		
		cout << "line contents: " << instance << endl;
		
		stringstream iss(instance); 
		string num_str;
		vector<string> numbers;
		
		while (getline(iss, num_str, ' '))
		{
			cout << num_str << " ";
			numbers.push_back(num_str);
		}
		cout << endl;
		
		int board_size = stoi(numbers[0], nullptr, 10);  // the first value in the line is the size of the chessboard
		Chessboard cb = Chessboard(board_size);  // create the chessboard
		cout << "chessboard size: " + to_string(board_size) + ", " + numbers[0] << endl;
		cb.print();
		
		// loop through rest of the string to get positions of the queens already on the board
		for (uint i = 1; i < numbers.size(); i += 2)
		{
			int col_pos = stoi(numbers[i + 1], nullptr, 10) - 1;
			int row_pos = stoi(numbers[i], nullptr, 10) - 1;
			cb.placeQueen(col_pos, row_pos);  // place queen
			cb.placed_queens ++;
		}
		
		cout << "printing cb with placed queens: " << endl;
		cb.print();
		
		stack<class Queen> recur_stack;
		Queen initial, stacktop;  // initial queen to use in stack recursion
	
		// Pushing all available spots
		for (int r = board_size - 1; r >= 0; r--)
		{
			for (int c = board_size - 1; c >= 0; c--)
			{
				if (cb.isSafe(c, r))
				{
					Queen safe = Queen(c, r);
					recur_stack.push(safe);
				}
			}
		}
		
		while (cb.placed_queens != board_size && !recur_stack.empty())
		{
			cout << "Placed queens: " << cb.placed_queens << endl;
			stacktop = recur_stack.top();
			recur_stack.pop();
			cout << "Considering " << stacktop.row_pos << " " << stacktop.col_pos << endl;
			
			if (cb.isSafe(stacktop.col_pos, stacktop.row_pos))
			{
				cb.placeQueen(stacktop.col_pos, stacktop.row_pos);
				cb.placed_queens ++;
				recur_stack.push(stacktop);
				for (int r = board_size - 1; r >= stacktop.row_pos + 1; r--)
				{
					for (int c = board_size - 1; c >= 0; c --)
					{
						if (cb.isSafe(c, r))
						{
							Queen safe = Queen(c, r);
							recur_stack.push(safe);
						}
					}
				}
			}
			else
			{
				cb.removeQueen(stacktop.col_pos, stacktop.row_pos);
				cout << "Removed queen " << stacktop.row_pos << " " << stacktop.col_pos << endl;
				cb.print();
				cb.placed_queens --;
			}
		}
		
		// Printing output to the output file
		if (cb.placed_queens == board_size)
		{
			for (int r = 0; r < board_size; r++)
			{
				for (int c = 0; c < board_size; c++)
				{
					if (cb[r][c] == 1)
						outfile << (r + 1) << " " << (c + 1) << " ";
				}
			}
			outfile << endl;
		}
		else
			outfile << "No solution" << endl;
	}
	
	// Close files
	infile.close();
	outfile.close();
	return 0;
	
}