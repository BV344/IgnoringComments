#ifndef IGNORECOMMENTS_TOKENIZER_HPP
#define IGNORECOMMENTS_TOKENIZER_HPP

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Tokenizer {
public:
    Tokenizer(std::string);
    char getToken();
    char whitespace(char c);

    void q2();
    void q3();
    void q4();


private:
    int lineNumber;
    std::string inputFileName;
    std::ifstream inputStream;
    ofstream output;
    bool charOfInterest(char c);
};



#endif //IGNORECOMMENTS_TOKENIZER_HPP
