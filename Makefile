CFLAGS = -g -Wall
CXX = g++

all: build/main.o
	$(CXX) $(CFLAGS) build/*.o -o IgnoreComments

build/main.o: src/main.cpp build/FileHandler.o build/CommentIdentifierDFA.o
	$(CXX) $(CFLAGS) -c src/main.cpp -o build/main.o

build/FileHandler.o: src/FileHandler.cpp build/CommentIdentifierDFA.o
	$(CXX) $(CFLAGS) -c src/FileHandler.cpp -o build/FileHanlder.o

build/CommentIdentifierDFA.o: src/CommentIdentifierDFA.cpp
	$(CXX) $(CFLAGS) -c src/CommentIdentifierDFA.cpp -o build/CommentIdentifierDFA.o

clean: 
	rm -rf IgnoreComments
	rm -rf build/*
