// Filename: chessboard.cpp

#include "chessboard.h"
#include "queen.h"
#include <cstdlib>
#include <array>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

Chessboard :: Chessboard(int s)
{
	size = s;
	cb = new int*[size];
	placed_queens = 0;
	for (int r = 0; r < size; r++)
	{
		cb[r] = new int[size];
		for (int c = 0; c < size; c++)
		{
			cb[r][c] = 0;
		}
	}
}

int *& Chessboard :: operator[] (int index)
{
	return cb[index];
}

Chessboard :: ~Chessboard()
{
	for (int r = 0; r < size; r++)
	{
		delete[] cb[r];
	}
	delete[] cb;
}

void Chessboard :: placeQueen(int col, int row)
{
	cout << "placing queen at " << row << " " << col << endl;
	// mark the attacking row positions of the queen
	for (int c = 0; c < size; c++)  // iterate through each column in the row
	{
		//cout << "before " << row << " " << c << ": " << cb[row][c] << endl;
		if (c != col)
			cb[row][c] -= 1;  // subtract one from the value at the position to represent the queen attacking
		//cout << "updated " << row << " " << c << ": " << cb[row][c] << endl;
	}
	
	// mark the attacking column positions of the queen
	for (int r = 0; r < size; r++)  // iterate through each row in the column
	{
		//cout << "before " << r << " " << col << ": " << cb[r][col] << endl;
		if (r != row)
			cb[r][col] -= 1;  // subtract one from the value at the position to represent the queen attacking
		//cout << "updated " << r << " " << col << ": " << cb[r][col] << endl;
	}
	
	// mark the diagonal attacking postitions of the queen
	// down and to the right diagonal reference to the postion of the queen
	for (int r = row + 1, c = col + 1; r < size && c < size; r++, c++)
	{
		//cout << "before " << r << " " << c << ": " << cb[r][c] << endl;
		cb[r][c] --;  // subtract one from the value at the position to represent the queen attacking that position
		//cout << "updated " << r << " " << c << ": " << cb[r][c] << endl;
	}
	// up and to the left diagonal in reference to the postion of the queen
	for (int r = row - 1, c = col - 1; r > 0 && c > 0; r--, c--)
	{
		//cout << "before " << r << " " << c << ": " << cb[r][c] << endl;
		cb[r][c] --;  // subtract one from the value at the position to represent the queen attacking that position
		//cout << "updated " << r << " " << c << ": " << cb[r][c] << endl;
	}
	// up and to the right diagonal in reference to the position of the queen
	for (int r = row - 1, c = col + 1; r > 0 &&  c < size; r--, c++)
	{
		//cout << "before " << r << " " << c << ": " << cb[r][c] << endl;
		cb[r][c] --;  // subtract one from the value at the position to represent the queen attacking that position
		//cout << "updated " << r << " " << c << ": " << cb[r][c] << endl;
	}
	// down and to the left diagonal in reference to the position of the queen
	for (int r = row + 1, c = col - 1; r < size && c > 0; r++, c--)
	{
		//cout << "updated " << r << " " << c << ": " << cb[r][c] << endl;
		cb[r][c] --;  // subtract one from the value at the position to represent the queen attacking that position
		//cout << "updated " << r << " " << c << ": " << cb[r][c] << endl;
	}
	
	cb[row][col] = 1;  // mark the position of the queen with a "1" to place it
	cout << "placed queen at " << row << " " << col << ": " << cb[row][col] << endl;
	
	print();
	
	return;
}

bool Chessboard :: isSafe(int col, int row)
{
	if (cb[row][col] == 0)  // 0 represents a safe positon
		return true;
	return false;
}

void Chessboard :: removeQueen(int col, int row)
{	
	// mark the attacking row positions of the queen
	for (int c = 0; c < size; c++)  // iterate through each column in the row
	{
		if (c != col)
			cb[row][c] += 1;  // add one from the value at the position to represent the queen not attacking that position
	}
	
	// mark the attacking column positions of the queen
	for (int r = 0; r < size; r++)  // iterate through each row in the column
	{
		if (r != row)
			cb[r][col] += 1;  // add one from the value at the position to represent the queen not attacking that position
	}
	
	// mark the diagonal attacking postitions of the queen
	// down and to the right diagonal reference to the postion of the queen
	for (int r = row + 1, c = col + 1; r < size && c < size; r++, c++)
	{
		cb[r][c] += 1;  // add one from the value at the position to represent the queen not attacking that position
	}
	// up and to the left diagonal in reference to the postion of the queen
	for (int r = row - 1, c = col - 1; r > 0 && c > 0; r--, c--)
	{
		cb[r][c] += 1;  // add one from the value at the position to represent the queen not attacking that position
	}
	// up and to the right diagonal in reference to the position of the queen
	for (int r = row - 1, c = col + 1; r > 0 && c < size; r--, c++)
	{
		cb[r][c] += 1;  // add one from the value at the position to represent the queen not attacking that position
	}
	// down and to the left diagonal in reference to the position of the queen
	for (int r = row + 1, c = col - 1; r < size && c > 0; r++, c--)
	{
		cb[r][c] += 1;  // add one from the value at the position to represent the queen not attacking that position
	}
	
	cb[row][col] = 0;  // mark the position of the queen with a 0 to remove it
	
	return;
}

void Chessboard :: print()
{
	for (int r = 0; r < size; r ++)
	{
		for (int c = 0; c < size; c ++)
		{
			cout << cb[r][c] << " ";
		}
		cout << endl;
	}
	return;
}