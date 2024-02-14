#include <fstream>
#include <iostream>
#include <vector>
#include "CommentIdentifierDFA.h"
#include "StringIdentifierDFA.h"
#include "FileHandler.h"


// openFile
void FileHandler::openFile(const std::string& filename) {
        fileStream.open(filename, std::ios::binary);
        if (!fileStream.is_open()) {
            std::cerr << "Error opening file: " << filename << "\n";
        }
        fileName = filename;
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
    int startLine;
    bool inComment = false;
    while (fileStream.get(ch)) {
        comment_dfa.processChar(ch);
        if(ch == '\n') {
            lineNumber++;
        }
        
        // If we are potentially inside a comment, push the character into the buffer
        if(comment_dfa.isActive()){
            if (!inComment) {
                startLine = lineNumber;
                inComment = true;
            }
            buffer.push_back(ch);
        }
        // If the comment DFA is not active, we have reached the end of a comment and need to flush the buffer
        else if (buffer.size() > 0){
            inComment = false;
            buffer.push_back(ch);
            if(comment_dfa.isComment == true){
                bufferToWhiteSpace();
            }
            flushBuffer();
        }
        else{
            fileContent += ch;

        }

        // if we're in an unended block comment, we can exit early
        if (comment_dfa.getState() == State::UNENDED_BLOCK_COMMENT) {
            std::cout << "ERROR: program contains C-style, unterminated comment on line " << startLine << std::endl;
            exit(12);
        }
    }

    State endState = comment_dfa.getState();
    std::cout << "END STATE " << endState << std::endl;

    // if we reach the last byte, and we're still in a C-style comment or double quote, throw error
    if (endState == State::DOUBLE_QUOTE) {
        std::cout << "ERROR: unterminated string literal on line " << lineNumber << std::endl;
        exit(-1);
    }
    if (comment_dfa.isComment == true && buffer.size() > 0){
        std::cout << "ERROR: program contains C-style, unterminated comment on line " << startLine << std::endl;
        exit(12);
    }
}

// bufferToWhiteSpace
// Buffer is converted to whitespace
void FileHandler::bufferToWhiteSpace(){
    for(int i = 0; i < buffer.size(); i++){
        if(buffer[i] == '\n'){
            //lineNumber++;
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

void FileHandler::printBuffer(){
    std::cout << "BUFFER: ";
    for(int i = 0; i < buffer.size(); i++) {
       std::cout << buffer[i];
    }
    std::cout << std::endl;
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
            lineNumber++;
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

FileHandler::FileHandler() {
    lineNumber = 1;
}

void FileHandler::outputToFile() {
    size_t lastIndex = fileName.find_last_of(".");
    std::string outputName = fileName.substr(0, lastIndex);
    outputName += "-comments_replaced_with_whitespace"
       + fileName.substr(lastIndex, fileName.length() - lastIndex + 1);

    std::ofstream outputFile(outputName); // Open File
    if (outputFile.is_open()) {
        outputFile << fileContent; // Write the string to the file
        outputFile.close();
        std::cout << "String has been written to " << outputName << " successfully." << std::endl;
    } else {
        std::cerr << "Unable to open " << outputName << " for writing." << std::endl;
    }

}
