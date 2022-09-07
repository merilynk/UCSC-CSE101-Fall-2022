// Filename: queen.h
//
// Header file for the class Queen that represents a queen in chess.

#ifndef QUEEN_H
#define QUEEN_H
#include <string>
using namespace std;

class Queen
{
	public:
		int col_pos;  // stores the column position of the queen
		int row_pos;  // stores the row position of the queen
		Queen();  // default constructor that sets the queen's position to (0,0)
		Queen(int col, int row);  // explicit constructor that sets the queen's position
		string printQueen();  // prints the position of the queen
};

#endif