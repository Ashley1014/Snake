cmake_minimum_required(VERSION 3.25)
project(Snake)

set(CMAKE_CXX_STANDARD 17)

add_executable(Snake main.cpp)

target_link_libraries(Snake ncurses)
