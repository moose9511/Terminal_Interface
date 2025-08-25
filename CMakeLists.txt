cmake_minimum_required(VERSION 4.0)
project(TerminalInterface)

set(CMAKE_CXX_STANDARD 20)

add_executable(TerminalInterface main.cpp
        fileStuff.cpp
        fileStuff.h
        Menu.cpp
        Menu.h
)

