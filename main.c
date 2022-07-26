#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
void print_chess_board(ChessBoard *board);
ChessBoard fill_chess_board();

int main()
{
    ChessBoard board = fill_chess_board();
    LookupTable tbls = fill_lookup_table();

    print_chess_board(&board);
    print_bitboard(board.occupied[both]);

    return 0;
}
