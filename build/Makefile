CFLAGS = -g -Wall
CXX = g++

all: main.o
	$(CXX) $(CFLAGS) *.o -o IgnoreComments
	rm -rf *.o

main.o: ../main.cpp FileHandler.o CommentIdentifierDFA.o
	$(CXX) $(CFLAGS) -c ../main.cpp

FileHandler.o: ../FileHandler.cpp CommentIdentifierDFA.o
	$(CXX) $(CFLAGS) -c ../FileHandler.cpp

CommentIdentifierDFA.o: ../CommentIdentifierDFA.cpp
	$(CXX) $(CFLAGS) -c ../CommentIdentifierDFA.cpp

clean: 
	rm -rf IgnoreComments
