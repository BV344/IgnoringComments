#include "../include/FileHandler.h"

int main(int argc, char *argv[]) {
	FileHandler fileHandler;

	// Procedure for opening a single file and printing the output
	fileHandler.openFile("tests/infiles/test4.c");
	fileHandler.printInitialFile();
	fileHandler.processFile();
	fileHandler.printStoredFile();

}
