CXX = g++
CXXFLAGS = -Wall

OBJECTS = graph.o sixdegrees.o

sixdegrees: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o sixdegrees graph.o sixdegrees.o

graph.o: graph.cpp graph.h
	$(CXX) -g $(CXXFLAGS) -c graph.cpp
	
sixdegrees.o: graph.cpp graph.h sixdegrees.cpp
	$(CXX) -g $(CXXFLAGS) -c sixdegrees.cpp

clean: 
	rm -f *.o
	rm treewrapper
	