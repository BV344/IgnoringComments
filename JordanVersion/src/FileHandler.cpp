#include <fstream>
#include <iostream>
#include <vector>
#include <sstream> // For std::stringstream
#include "../include/CommentIdentifierDFA.h"
#include "../include/StringIdentifierDFA.h"
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
    if (!fileStream.is_open()) {
        std::cerr << "Error: File stream is not open.\n";
        return;
    }

    StringIdentifierDFA string_dfa;
    CommentIdentifierDFA comment_dfa;

    char ch;
    while (fileStream.get(ch)) {
        string_dfa.processChar(ch);
        // If we're inside a string literal, we don't care about comments
        if(string_dfa.isString()){
            fileContent += ch;
        }
        // Else, check if we're inside a comment
        else{
            comment_dfa.processChar(ch);
            // If we are potentially inside a comment, push the character into the buffer
            if(comment_dfa.isActive()){
                buffer.push_back(ch);
            }
            // If the comment DFA is not active, we have reached the end of a comment and need to flush the buffer
            else if (buffer.size() > 0){
                bufferToWhiteSpace();
                flushBuffer();
            }
            else{
                fileContent += ch;
            }
        }
    }
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
