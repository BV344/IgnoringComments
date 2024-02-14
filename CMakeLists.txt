cmake_minimum_required(VERSION 3.20)
project(IgnoreComments)

set(CMAKE_CXX_STANDARD 20)

add_executable(IgnoringComments main.cpp
        FileHandler.cpp
        FileHandler.h
        CommentIdentifierDFA.cpp
        CommentIdentifierDFA.h
)
