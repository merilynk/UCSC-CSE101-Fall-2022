CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = nqueens.o chessboard.o queen.o

nqueens: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o $@ $^
	
clean:
	rm -f *o 
	rm nqueens

$(OBJECTS): chessboard.h queen.h