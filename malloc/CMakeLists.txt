cmake_minimum_required(VERSION 3.17)
project(malloc C)

set(CMAKE_C_STANDARD 11)

add_executable(malloc test.c dlmall.c dlmall.h)