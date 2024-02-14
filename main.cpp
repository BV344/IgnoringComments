#include "FileHandler.h"

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(1);
    }
	FileHandler fileHandler;

	// Procedure for opening a single file and printing the output
	fileHandler.openFile(argv[1]);
//	fileHandler.printInitialFile();
	fileHandler.processFile();
	fileHandler.printStoredFile();
   fileHandler.outputToFile();

}
