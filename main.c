#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
Bitboard queen_move(Bitboard bishop_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls);
void print_chess_board(struct bit_chess_board *board);
ChessBoard fill_chess_board();

int main()
{

    Bitboard bishop_pos = 0, own_side = 0, enemy_side = 0;
    SET_BIT(bishop_pos, e4);
    SET_BIT(own_side, g6);
    SET_BIT(enemy_side, c2);
    LookupTable tbls = fill_lookup_table();
    Bitboard r = queen_move(bishop_pos, own_side, enemy_side, &tbls);
    print_bitboard(r);



    return 0;
}
