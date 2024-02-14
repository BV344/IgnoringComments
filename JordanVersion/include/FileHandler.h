// FileHandler.h
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <iostream>
#include <fstream>

class FileHandler {
public:

 	std::ifstream fileStream;
    std::string fileContent;

    void openFile(const std::string& filename);

    // Stream Solution
    void processFile();
    
    // Print file from stream vs print file from string storage
    void printInitialFile();
    void printStoredFile();

    ~FileHandler() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }

private:
    std::vector<char> buffer;
    void bufferToWhiteSpace();
    void flushBuffer();
};

#endif // FILEHANDLER_H
