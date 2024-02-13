// CommentIdentifierDFA.h
#ifndef COMMENT_IDENTIFIER_DFA_H
#define COMMENT_IDENTIFIER_DFA_H

#include <string>
#include <vector>

class CommentIdentifierDFA {
public:
    enum class State {
        START,
        SLASH,
        BLOCK_COMMENT,
        LINE_COMMENT,
        BLOCK_COMMENT_END,
        BLOCK_COMMENT_END_SLASH
    };

    CommentIdentifierDFA();

    bool processChar(char ch);

    bool isComment() const;

    void reset();

    State getState() const { return state_; }

private:
    State state_;
};

#endif // COMMENT_IDENTIFIER_DFA_H
