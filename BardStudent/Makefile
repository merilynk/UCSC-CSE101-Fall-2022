CXX = g++
CXXFLAGS = -Wall -O2

OBJECTS = linkedlist.o bard.o

bard: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o bard bard.o linkedlist.o
	
linkedlist.o: linkedlist.cpp linkedlist.h
	$(CXX) -g $(CXXFLAGS) -c linkedlist.cpp
	
bard.o: linkedlist.cpp linkedlist.h bard.cpp
	$(CXX) -g $(CXXFLAGS) -c bard.cpp
	
clean: 
	rm -f *.o
	rm bard