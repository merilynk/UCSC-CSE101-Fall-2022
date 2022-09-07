// Filename: chessboard.h
//
// Header file for the class Chessboard that represents a chessboard.

#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <array>
using namespace std;

class Chessboard
{
	private:
		int size;  // stores the size of the chessboard
		int **cb;  // uses a 2d array to represent the chessboard
	public:
		int placed_queens;
		int *& operator[] (int index);
		Chessboard(int s);  // explicit constructor for the chessboard that specifies the size
		~Chessboard();
		void placeQueen(int col, int row);  // places a queen on the chessboard and marks all positions that queen can attack
		bool isSafe(int col, int row);  // checks if the position of the queen is safe
		void removeQueen(int col_pos, int row_pos);  // removes the queen from the chessboard and unmarks all the positions it could attack	
		void print();  // prints the 2d array that represents the chessboard
};

#endif
