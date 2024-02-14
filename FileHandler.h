// FileHandler.h
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class FileHandler {
public:
    FileHandler();

 	std::ifstream fileStream;
    std::string fileContent;
    std::ofstream fileOutput;

    void openFile(const std::string& filename);
    void outputToFile();
    // Stream Solution
    void processFile();
    
    // Print file from stream vs print file from string storage
    void printInitialFile();
    void printStoredFile();

    void printBuffer();

    ~FileHandler() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }

private:
    std::string fileName;
    std::vector<char> buffer;
    void bufferToWhiteSpace();
    void flushBuffer();
    int lineNumber;
};

#endif // FILEHANDLER_H
