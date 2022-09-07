// Filename: graph.cpp

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

Graph :: Graph ()
{
	return;
}
	
void Graph :: addMovie(string movieTitle, vector<string> actors)
{
	Movie m;  // initalize a new movie
	m.title = movieTitle; // set the movie title
	movies.insert(m);  // add the movie into set of movies if it wasn't already in there
	vector<Actor*> a_vector;  //  initialize an empty vector of Actors
	for (string a : actors)  // for each actor name in the actors vector
	{
		Actor *new_actor = new Actor();  // initialize a new actor
		new_actor->name = a;  // set the new actor's name
		
		set<Actor*> :: iterator it = (this->actors).find(new_actor);
		if (it != this->actors.end())
		{
			delete new_actor;
			new_actor = *it;
		}
		
		a_vector.push_back(new_actor);  // add the actor into the movie's vector of actors
		this->actors.insert(new_actor);  // add the new actor into the set of actors if it wasn't already in there
	}
		
	for (Actor *a : a_vector)  // for each actor in the movie's vector of actors
	{
		m.m_actors.push_back(*a);  // insert the movie's 
	}
		
	for (Actor *a : a_vector)
	{
		for (Actor *b : a_vector)
		{
			if (a->name != b->name)  // for each actor in the movie, compare it with the rest of the actors in the movie
			{
				a->neighbors[b->name] = m;  // neighbor is b, through the movie
				b->neighbors[a->name] = m;  // neighbor is a, through the movie
			}
		}
	}
}
	
void Graph :: printGraph()
{
	for (const auto& a : actors)  // for each actor in set of actors
	{
		cout << a->name << " --> ";  // print out the current actor name
		for (auto& n : a->neighbors)  // for each actor in neighbors list
		{
			cout << n.first << " ";  //print out the name of the neighbor
		}
		cout << endl;  // create a new line
	}
}


void Graph :: BFS(string startStr, string endStr, ofstream& output)
{
	if (startStr == endStr)
	{
		output << startStr << endl;
		return;
	}
	// Do a BFS starting at startStr Actor in graph
	cout << "Setting up for bfs...";
	// Do a BFS starting at startStr Actor in graph
	int graphSize = actors.size();
	queue<Actor*> q;  // initialize a queue
	Actor *startActor = new Actor(); 
  startActor->name = startStr;
  set<Actor*> :: iterator s = (this->actors).find(startActor);

  Actor *endActor = new Actor(); 
  endActor->name = endStr;

	q.push(*s);  // enqueue start
	vector<bool> visited (graphSize, false);  // keeps track of visited nodes in graph
	vector<Actor*> pred (graphSize, NULL);  // predecessor
	cout << "done" << endl;
  
  cout << "While queue not empty...";
	while (!q.empty())
	{
		Actor *current = q.front();  // get the first node
		q.pop();  // dequeue
		
		int i = 0;  // keeps track of index for arrays
		for (auto& n : current->neighbors)
		{
			if (visited[i] == false)
			{
				visited[i] = true;
        Actor *person = new Actor(); 
        person->name = n.first;
				set<Actor*> :: iterator a = (this->actors).find(person);
				pred[i] = *a;
				q.push(*a);
			}
			i ++;	
		}
	}
  cout << "done." << endl;

  cout << "Creating path ...";
	// create the path by reversing predecessor array
  reverse(pred.begin(), pred.end());
	if (pred.empty())
	{
		output << "Not present" << endl;
		return;
	}
	
  output << startStr <<  "-( " << pred[0]->neighbors[startStr].title << ")- ";
	for (uint i = 0; i < pred.size(); i ++)
	{
    if (pred[i] == NULL)
      continue;
    if (pred[i]->name == endStr)
    {
      output << pred[i]->name << endl;
      break;
    }
    output << pred[i]->name << "-( " << pred[i]->neighbors[pred[i + 1]->name].title << ")- ";
	}
  cout << "done.";
	return;
}