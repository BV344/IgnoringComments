// CommentIdentifierDFA.cpp
#include "../include/CommentIdentifierDFA.h"

CommentIdentifierDFA::CommentIdentifierDFA() : state_(State::START) {}

bool CommentIdentifierDFA::processChar(char ch) {
    switch (state_) {
        case State::START:
            if (ch == '/') {
                state_ = State::SLASH;
            }
            break;
        case State::SLASH:
            if (ch == '*') {
                state_ = State::BLOCK_COMMENT;
            } else if (ch == '/') {
                state_ = State::LINE_COMMENT;
            } else {
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
    return isComment();
}

bool CommentIdentifierDFA::isComment() const {
    return state_ == State::LINE_COMMENT || state_ == State::BLOCK_COMMENT || state_ == State::BLOCK_COMMENT_END;
}

void CommentIdentifierDFA::reset() {
    state_ = State::START;
}
