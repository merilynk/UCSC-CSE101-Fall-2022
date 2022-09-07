// Filename: graph.h

#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <functional>
using namespace std;

class Movie;
class Actor;

class Movie {  
	public:
		string title;  // movie name
		vector<Actor> m_actors;  // list of actors in that movie
		bool operator< (const Movie & other) const  // creates a comparison operator for Movie data type
		{
			return (title < other.title);
		}
};

// custom specialization of std::hash can be injected in namespace std
template<>
struct std::hash<Movie>
{
	std::size_t operator()(Movie const& m) const noexcept
	{
		return std::hash<std::string>{}(m.title);
	}
};

class Actor {  
	public: 
		string name;  // name of actor
		unordered_map<string, Movie> neighbors;  // unordered map of the actor's neighbors in the
		bool operator< (const Actor & other) const  // creates a comparison operator for Actor data type
		{
			return (name < other.name);
		}
};

// custom specialization of std::hash can be injected in namespace std
template<>
struct std::hash<Actor>
{
	std::size_t operator()(Actor const& a) const noexcept
	{
		return std::hash<std::string>{}(a.name);
	}
};

struct actorptrcmp
{
	bool operator()(const Actor* lhs, const Actor* rhs)const
	{
		return lhs->name < rhs->name;
	}
};

class Graph {
	private:
		set<Movie> movies; 
		set<Actor*, actorptrcmp> actors;  
	public:
		Graph();  // constructor
		void addMovie(string, vector<string>);  // adds a movie to the graph
		void printGraph();  // prints the actors and their neigbors
		void BFS(string, string, ofstream&);  // performs a breadth first search given a starting node and ending node
};

#endif