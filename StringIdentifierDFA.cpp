// StringIdentifierDFA.cpp
#include "StringIdentifierDFA.h"

StringIdentifierDFA::StringIdentifierDFA() : state_(State::START) {}

bool StringIdentifierDFA::processChar(char ch) {
    switch (state_) {
        case State::START:
            if (ch == '"') {
                state_ = State::STRING_BODY;
            }
            break;
        case State::STRING_BODY:
            if (ch == '"') {
                    state_ = State::START;
                }
                break;
        default:
            break;
    }
    return isString();
}

bool StringIdentifierDFA::isString() const {
    return state_ == State::STRING_BODY;
}

void StringIdentifierDFA::reset() {
    state_ = State::START;
}
