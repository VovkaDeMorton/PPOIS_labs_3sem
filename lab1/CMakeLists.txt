cmake_minimum_required(VERSION 3.15)
project(lab1_oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(lab1_app
    src/main.cpp
    src/TicTacToe.cpp
)