// CommentIdentifierDFA.cpp
#include "CommentIdentifierDFA.h"

CommentIdentifierDFA::CommentIdentifierDFA() : state_(State::START) {}

std::ostream &operator << (std::ostream& strm, State s){

     const std::string name[] = {"START", "SLASH", "BLOCK_COMMENT", "LINE_COMMENT", 
        "BLOCK_COMMENT_END", "DOUBLE_QUOTE", "UNENDED_BLOCK_COMMENT_START", "UNENDED_BLOCK_COMMENT"};
     return strm << name[s];
}

void CommentIdentifierDFA::processChar(char ch) {
    switch (state_) {
        case State::START:
            if (ch == '"') {
                state_ = State::DOUBLE_QUOTE;
            }
            else if (ch == '/') {
                state_ = State::SLASH;
            }
            else if (ch == '*') {
                state_ = State::UNENDED_BLOCK_COMMENT_START;
            }
            if(isComment == true){
                isComment = false;
            }
            break;
        case State::SLASH:
            if (ch == '*') {
                isComment = true;
                state_ = State::BLOCK_COMMENT;
            } else if (ch == '/') {
                isComment = true;
                state_ = State::LINE_COMMENT;
            } else {
                isComment = false;
                state_ = State::START;
            }
            break;
        case State::BLOCK_COMMENT:
            if (ch == '*') {
                state_ = State::BLOCK_COMMENT_END;
            }
            break;
        case State::BLOCK_COMMENT_END:
            if (ch == '/') {
                state_ = State::START;
            } else if (ch != '*') {
                state_ = State::BLOCK_COMMENT;
            }
            break;
        case State::LINE_COMMENT:
            if (ch == '\n') {
                state_ = State::START;
            }
            break;
        case State::DOUBLE_QUOTE:
            if (ch == '"') {
                state_ = State::START;
            }
            break;
        case State::UNENDED_BLOCK_COMMENT_START:
            if (ch == '/') {
                state_ = State::UNENDED_BLOCK_COMMENT;
            }
        default:
            break;
    }
}

bool CommentIdentifierDFA::isActive() const {
    return state_ != State::START;
}

void CommentIdentifierDFA::reset() {
    state_ = State::START;
}
