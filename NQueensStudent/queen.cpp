// Filename: queen.cpp

#include "queen.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

Queen :: Queen()
{
	col_pos = 0;
	row_pos = 0;
}

Queen :: Queen(int col, int row)
{
	col_pos = col;
	row_pos = row;
}

string Queen :: printQueen()
{
	return to_string(col_pos) + " " + to_string(row_pos) + " ";
}