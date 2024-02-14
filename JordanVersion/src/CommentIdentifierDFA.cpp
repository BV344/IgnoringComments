// CommentIdentifierDFA.cpp
#include "../include/CommentIdentifierDFA.h"
#include <iostream>

CommentIdentifierDFA::CommentIdentifierDFA() : state_(State::START) {}

void CommentIdentifierDFA::processChar(char ch) {
    switch (state_) {
        case State::START:
            if (ch == '/') {
                state_ = State::SLASH;
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
