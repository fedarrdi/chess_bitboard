cmake_minimum_required(VERSION 3.21)
project(chess_bit_boards C)

set(CMAKE_C_STANDARD 99)

add_executable(chess_bit_boards main.c chess_types.h piece_movement.c init_functions.c)
