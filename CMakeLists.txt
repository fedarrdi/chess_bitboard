cmake_minimum_required(VERSION 3.21)
project(chess_bit_boards C)

set(CMAKE_C_STANDARD 99)

add_executable(chess_bit_boards main.c chess_types.h piece_movement.c init_functions.c player_interface.c move_generation.c make_move.c get_best_move.c evalute_position.c piece_movement.h move_generation.h player_interface.h make_move.h init_functions.h get_best_move.h evalute_position.h zobrist_hashing.c zobrist_hashing.h)
