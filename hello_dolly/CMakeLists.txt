cmake_minimum_required(VERSION 3.17)
project(hello_dolly C)

set(CMAKE_C_STANDARD 99)

add_executable(hello_dolly main.c zombie.c hello_dolly.h)