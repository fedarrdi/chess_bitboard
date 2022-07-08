#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
void print_chess_board(ChessBoard *board);
ChessBoard fill_chess_board();
void player_play_move(ChessBoard *board, enum color color, LookupTable *tbls);

int main()
{
    ChessBoard board = fill_chess_board();
    LookupTable tbls = fill_lookup_table();
    print_chess_board(&board);
    for(int i = 0;i < 10;i++)
    {
        player_play_move(&board, white, &tbls);
        print_chess_board(&board);
    }
    return 0;
}
