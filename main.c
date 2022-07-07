#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
Bitboard rook_move(Bitboard rook_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls);
void print_chess_board(struct bit_chess_board *board);
ChessBoard fill_chess_board();

int main()
{

    Bitboard rook_pos = 0, own_side = 0, enemy_side = 0;
    SET_BIT(rook_pos, e4);
    SET_BIT(own_side, e8);
    SET_BIT(enemy_side, c4);
    LookupTable tbls = fill_lookup_table();
    Bitboard r = rook_move(rook_pos, own_side, enemy_side, &tbls);
    print_bitboard(r);



    return 0;
}
