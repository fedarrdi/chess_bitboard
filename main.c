#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
Bitboard black_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls);

int main()
{
    Bitboard board = 0;
    SET_BIT(board, a5);

    Bitboard own_side = 0, enemy_side = 0;
    LookupTable tbls = fill_lookup_table();

    SET_BIT(enemy_side, h4);


    Bitboard o = black_pawn_move(board, own_side, enemy_side, &tbls);
    print_bitboard(o);

    return 0;
}
