CXX = g++
CXXFLAGS = -Wall

OBJECTS = avl.o node.o wordrange.o

wordrange: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o wordrange wordrange.o avl.o node.o
	
avl.o: avl.cpp avl.h node.h
	$(CXX) -g $(CXXFLAGS) -c avl.cpp
	
node.o: node.h node.cpp
	$(CXX) -g $(CXXFLAGS) -c node.cpp

clean:
	rm -f *.o
	rm wordrange