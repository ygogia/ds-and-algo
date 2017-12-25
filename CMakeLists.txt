cmake_minimum_required(VERSION 3.8)
project(ds_and_algo)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES stack.h)
set(SOURCE_FILES tree.h)
set(SOURCE_FILES main.c structures.h tree_queue.h)

add_executable(ds_and_algo ${SOURCE_FILES})