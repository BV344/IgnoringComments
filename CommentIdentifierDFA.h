// CommentIdentifierDFA.h

/**
 * The CommentIdentifierDFA class implements a deterministic finite automaton (DFA) 
 * to identify comments within a stream of characters. It is designed to support 
 * both block comments (delimited by "/asterisk" and "asterisk/") and line comments (delimited by "//" and "\n").
 * 
 * Key Features:
 *  - Employs a procedural state machine to transition between states based on the current character in the stream.
 * 
 * Usage Conditions:
 *  - Initialize the DFA, which sets the state to START.
 *  - For each character in the input stream, call processChar(char ch) to process the character through the DFA.
 *  - At any point, isActive() can be queried to determine if the DFA is within a comment or an potential initial delimiter '/'+...
 * 
 * This class is designed for preprocessing C/C++ files.
 */

#ifndef COMMENT_IDENTIFIER_DFA_H
#define COMMENT_IDENTIFIER_DFA_H

#include <string>
enum class State {
    START,
    SLASH,
    BLOCK_COMMENT,
    LINE_COMMENT,
    BLOCK_COMMENT_END,
    DOUBLE_QUOTE,
};

#include <vector>

class CommentIdentifierDFA {
public:

    CommentIdentifierDFA();

    void processChar(char ch);

    bool isActive() const;
    bool isComment;

    void reset();

    State getState() const { return state_; }

private:
    State state_;
};

#endif // COMMENT_IDENTIFIER_DFA_H
