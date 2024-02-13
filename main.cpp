#include "Tokenizer.hpp"
#include <ostream>
using namespace std;

int main(int argc, char *argv[]) {

    if( argc != 2 ) {  // we expect the name of the file as an argument to the program.
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile" << std::endl;
        exit(1);
    }

    // Here, we open the file to make sure that it exists before starting the program.
    // When using CLion, the input file has to be in cmake-build-debug directory.
    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);    // open for reading
    if( ! inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        std::cout << strerror(errno) << std::endl;
        exit(2);
    }
    inputStream.close();

    Tokenizer tokenizer(argv[1]);
    ofstream outputFile;

    outputFile.open("output.txt");

    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open the file for writing." << endl;
        exit(4); // Exit with error code 4
    }


    tokenizer.getToken();
    tokenizer.getToken();
    tokenizer.getToken();
    tokenizer.getToken();

    return 0;
}


