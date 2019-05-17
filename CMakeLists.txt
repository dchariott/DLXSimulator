cmake_minimum_required(VERSION 3.13)
project(DLXSimulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(DLXSimulator main.cpp StateMachine.cpp StateMachine.h DataPath.cpp DataPath.h)