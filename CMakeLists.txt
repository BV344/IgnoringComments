cmake_minimum_required(VERSION 3.27)
project(IgnoreComments)

set(CMAKE_CXX_STANDARD 20)

add_executable(IgnoreComments main.cpp
        Tokenizer.cpp
        Tokenizer.hpp
)
