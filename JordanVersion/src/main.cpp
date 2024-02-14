#include "../include/FileHandler.h"
#include <iostream>
#include <fstream>

/*
Usage:
Run as ./aone test2.c test3.c etc...
with filenames in the tests/infiles folder

*/
int main(int argc, char *argv[]) {
    // Check if there are any command-line arguments
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
			std::string fileName = std::string(argv[i]);
            std::string filePath = "tests/infiles/" + fileName;
            std::ifstream testFile(filePath);

            // Check if the file exists before attempting to process it
            if (testFile.good()) {
                FileHandler fileHandler;

                std::cout << "\n--------------------------------\n" << fileName << std::endl;

                fileHandler.openFile(filePath);
				std::cout << "BEFORE " << std::endl;
				std::cout << "--------------------------------\n";
                fileHandler.printInitialFile();
                fileHandler.processFile();
				std::cout << "--------------------------------\n";
				std::cout << "AFTER " << std::endl;
				std::cout << "--------------------------------\n";
                fileHandler.printStoredFile();

            } else {
                std::cerr << "File not found or cannot be opened: " << filePath << std::endl;
            }

            // Close the ifstream
            testFile.close();
        }
    } else {
        std::cerr << "Usage: " << argv[0] << " <filename1> <filename2> ..." << std::endl;
    }

    return 0;
}
