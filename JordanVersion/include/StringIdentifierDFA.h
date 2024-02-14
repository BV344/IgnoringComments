// CommentIdentifierDFA.h
#ifndef STRING_IDENTIFIER_DFA_H
#define STRING_IDENTIFIER_DFA_H

#include <string>
#include <vector>

class StringIdentifierDFA {
public:
    enum class State {
        START,
        STRING_BODY
    };

    StringIdentifierDFA();

    bool processChar(char ch);

    bool isString() const;

    void reset();

    State getState() const { return state_; }

private:
    State state_;
};

#endif // STRING_IDENTIFIER_DFA_H
