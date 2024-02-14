cmake_minimum_required(VERSION 3.24)
project(IgnoreComments)

set(CMAKE_CXX_STANDARD 20)

add_executable(IgnoreComments main.cpp
        FileHandler.cpp
        FileHandler.h
        CommentIdentifierDFA.cpp
        CommentIdentifierDFA.h
        StringIdentifierDFA.cpp
        StringIdentifierDFA.h
)
