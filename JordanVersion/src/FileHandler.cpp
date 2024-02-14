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

// Core Character Stream to Comment Removal
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
        if(comment_dfa.isComment == false){
        string_dfa.processChar(ch);
        }
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
                buffer.push_back(ch);
                if(comment_dfa.isComment == true){
                    bufferToWhiteSpace();
                }
                flushBuffer();
            }
            else{
                fileContent += ch;
            }
        }
    }
    if (comment_dfa.isComment == true && buffer.size() > 0){
        std::cout << "there is an error" << std::endl;
    }
}

// bufferToWhiteSpace
// Buffer is converted to whitespace
void FileHandler::bufferToWhiteSpace(){
    for(int i = 0; i < buffer.size(); i++){
        if(buffer[i] == '\n'){
            continue;
        }
        buffer[i] = ' ';
    }
}

// flushBuffer
// Buffer is written to fileContent then cleared
void FileHandler::flushBuffer(){
    for(int i = 0; i < buffer.size(); i++){
        fileContent += buffer[i];
    }
    buffer.clear();
}

// printInitialFile
// reads and prints the fileStream then resets its position back to where it was before
void FileHandler::printInitialFile() {
        if (!fileStream) {
            std::cerr << "Stream is not open." << std::endl;
            return;
        }

        // Save the current position of the file stream
        std::streampos originalPosition = fileStream.tellg();

        // Reset to the start of the file
        fileStream.seekg(0, std::ios::beg);

        // Read and print the file contents
        std::string line;
        while (getline(fileStream, line)) {
            std::cout << line << std::endl;
        }

        // Restore the file stream's position and state
        fileStream.clear(); // Clear any flags
        fileStream.seekg(originalPosition);

        // Confirm the restoration
        std::streampos newPosition = fileStream.tellg();
        if (newPosition != originalPosition) {
            std::cerr << "Failed to restore the stream position." << std::endl;
        }
    }

void FileHandler::printStoredFile() {
    std::cout << fileContent;
}
