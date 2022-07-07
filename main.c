#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
Bitboard black_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls);
void print_chess_board(struct bit_chess_board *board);
ChessBoard fill_chess_board();

int main()
{
    ChessBoard board = fill_chess_board();
    print_chess_board(&board);






    return 0;
}
