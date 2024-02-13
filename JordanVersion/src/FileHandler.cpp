#include <fstream>
#include <iostream>
#include <vector>
#include <sstream> // For std::stringstream
#include "../include/CommentIdentifierDFA.h"
#include "../include/FileHandler.h"


// openFile
void FileHandler::openFile(const std::string& filename) {
        fileStream.open(filename, std::ios::binary);
        if (!fileStream.is_open()) {
            std::cerr << "Error opening file: " << filename << "\n";
        }
    }

// processFile
void FileHandler::processFile() {
    // if (!fileStream.is_open()) {
    //     std::cerr << "Error: File stream is not open.\n";
    //     return;
    // }

    // CommentIdentifierDFA dfa;
    // std::vector<char> buffer;
    // bool mightBeComment = false;

    // char ch;
    // while (fileStream.get(ch)) {
    //     if (!mightBeComment) {
    //         if (ch == '/') {
    //             mightBeComment = true;
    //             buffer.push_back(ch);
    //             continue;
    //         }
    //         std::cout << ch;
    //     } else {
    //         buffer.push_back(ch);
    //         if (dfa.processChar(ch)) {
    //             flushBufferAsSpaces(buffer);
    //             mightBeComment = false;
    //         } else if (buffer.size() > 1 /*&& !dfa.isInComment()*/) {
    //             flushBuffer(buffer);
    //             mightBeComment = false;
    //         }
    //     }
    // }

    // if (!buffer.empty()) {
    //     flushBuffer(buffer);
    // }
}

// Function to read entire file content into a string
void FileHandler::storeFileInMemory() {
    if (!fileStream.is_open()) {
        std::cerr << "Error: File stream is not open.\n";
        return;
    }

    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    fileContent = buffer.str();
}

void FileHandler::printStoredFile() {
    std::cout << fileContent;
}
