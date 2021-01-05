cmake_minimum_required(VERSION 3.17)
project(green_threads C)

set(CMAKE_C_STANDARD 11)

add_executable(green_threads main.c green.h green.c)