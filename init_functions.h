#include "chess_types.h"

#ifndef CHESS_BIT_BOARDS_INIT_FUNCTIONS_H
#define CHESS_BIT_BOARDS_INIT_FUNCTIONS_H
void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
ChessBoard parse_FEN(const char *FEN);
Positions init_position_arr();


#endif //CHESS_BIT_BOARDS_INIT_FUNCTIONS_H
