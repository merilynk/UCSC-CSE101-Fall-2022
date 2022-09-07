// Filename: sixdegrees.cpp

#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

int main(int argc, char** argv)
{
	if (argc < 3)  // must provide the two arguments
	{
		throw std::invalid_argument("Usage: ./sixdegrees <INPUT FILE> <OUTPUT FILE>");  // throw error
	}
	
	ifstream moviesFile;  // file stream for cleaned_movielist.txt
	moviesFile.open("cleaned_movielist.txt");  // open movie list text file
	
	Graph g;  // initialize a graph
	
	// Parse movie list file
	string line;  // to store the next line of the movie list file
	
	while (getline(moviesFile, line))
	{
		stringstream ssLine(line);  // create a string stream for the line
		string str;
		vector<string> actorsList;  // vector to store list of actors from the current line
		
		// Parse string stream
		getline(ssLine, str, ' ');
		string movieTitle = str;
		//cerr << movieTitle << ": ";
		while (getline(ssLine, str, ' '))  // tokenize on spaces
		{
			actorsList.push_back(str);  // insert the actor's name into the vector
			//cerr << str << " ";
		}
		//cerr << endl;
		
		g.addMovie(movieTitle, actorsList);  // add the movie into the graph
	}
	
	// Parse command line options and open file streams
	ifstream infile;  // stream for input file
	ofstream outfile;  // stream for output file
	infile.open(argv[1]);  // open input file
	outfile.open(argv[2]);  // open output file
	char *pr, *valstr;  // to use with tokenizing
	string startActor, endActor;  
	
	// Parse input file
	// Set the starting node and ending node
	string pathRange;  // to store the next line in the input file
	
	while (getline(infile, pathRange))  // get next line of infile
	{
		if (pathRange.length() == 0)  // check for empty line in file
			continue;
		pr = strdup(pathRange.c_str());  // copy string into a "C-style" string
		valstr = strtok(pr, " \t");
		if (valstr != NULL)
			startActor = valstr;
		valstr = strtok(NULL, " \t");
		if (valstr != NULL)
			endActor = valstr;
		cout << startActor << " " << endActor << endl;
		
		// Peform a BFS to find a path.
		g.BFS(startActor, endActor, outfile);
	}
	
	// Close streams
	moviesFile.close();
	infile.close();
	outfile.close();
}