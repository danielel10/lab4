cmake_minimum_required(VERSION 3.22)
project(lab4 C)

set(CMAKE_C_STANDARD 11)

include_directories(task0a)
include_directories(task0b)
include_directories(task1a)

add_executable(lab4
        task0a/main.c
        task0a/util.c
        task0a/util.h
        task0b/main.c
        task0b/util.c
        task0b/util.h
        task1a/main.c
        task1a/util.c
        task1a/util.h)
