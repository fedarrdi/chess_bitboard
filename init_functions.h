#include "chess_types.h"

#ifndef CHESS_BIT_BOARDS_INIT_FUNCTIONS_H
#define CHESS_BIT_BOARDS_INIT_FUNCTIONS_H
void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
ChessBoard parse_FEN(const char *FEN);
Positions init_position_arr();
MoveList init_move_list();


#endif //CHESS_BIT_BOARDS_INIT_FUNCTIONS_H
