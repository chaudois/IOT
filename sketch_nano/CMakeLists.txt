cmake_minimum_required(VERSION 3.13)
project(sketch_nano)

set(CMAKE_CXX_STANDARD 14)

add_executable(sketch_nano main.cpp Mockup.cpp game.hpp game.cpp  controller.hpp controller.cpp)