cmake_minimum_required(VERSION 3.25)
project(SCPI_parse C)

set(CMAKE_C_STANDARD 99)

add_executable(SCPI_parse main.c parser.c parser.h)
