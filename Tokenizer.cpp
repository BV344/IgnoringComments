#include "Tokenizer.hpp"

Tokenizer::Tokenizer(string name) {
    lineNumber = 1;
    inputFileName = name;
    inputStream.open(inputFileName);
    output.open("output.txt");
}

bool Tokenizer::charOfInterest(char c) {
    // is c the initial (or the sole) character of a token?

    if(c == '/'){
        return true;
    }
    return false;

}

char Tokenizer::whitespace(char c) {
    c = ' ';
}

char Tokenizer::getToken() {
    char c;

    if( ! inputStream.is_open()) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(5);
    }

    while(inputStream.get(c) && !charOfInterest(c)){
        output << c;
        if(c == '\n'){
            lineNumber++;// Keeps track of the line number
        }
    }

    if(c == '/'){//Now we begin the tokenization
        if(inputStream.peek() == '/'){
            q2();
        }
        else if(inputStream.peek() == '*'){
            q3();

        }
        else{
            cout << "Syntax Error: Improper comments" << endl;
            exit(5);
        }
    }
}

void Tokenizer::q2() {
    char c;
    output << ' ';
    while(inputStream.get(c) && c != '\n'){
        c = ' ';
        output << c;
    }
    output << '\n';
}

void Tokenizer::q3(){
    char c = ' ';
    output << c;
    inputStream.get(c);
    output << ' ';
    while(inputStream.get(c) && c != '*'){
        if(c == '\n') {
            lineNumber++;
            output << '\n';
        }

    }
    if(c == '*')
        q4();
    if(inputStream.eof()){
        cout << "ERROR: Program contains C-style, unterminated comment on line " << lineNumber << endl;
        exit(1);
    }

}

void Tokenizer::q4(){
    char c;

    if(inputStream.get(c) && c == '/')
        return;

    if(inputStream.get(c) && c != '*'){
        q3();
    }

    while(inputStream.get(c) && c == '*'){
        cout << "q4c: " << c << endl;
        c = ' ';
        output << c;
    }
    inputStream.get(c);
    if(c == '/')
        return;

}
