cmake_minimum_required(VERSION 3.25)
project(test_ergasia3 C)
MATH(EXPR stack_size "32 * 1024 * 1024") # 32 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
set(CMAKE_C_STANDARD 11)

add_executable(test_ergasia3 main.c kruskal.h reverse_delete.h)
