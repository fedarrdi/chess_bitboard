#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
void print_chess_board(ChessBoard *board);
ChessBoard fill_chess_board();
void generate_position_moves(const ChessBoard *board, enum color side, const LookupTable *tbls);
void parse_FEN(const char *FEN, ChessBoard *board);

int main()
{
    ChessBoard board;
    parse_FEN("r1b1k1nr/p2p1pNp/n2B4/1p1NP2P/6P1/3P1Q2/P1P1K3/q5b1", &board);
    LookupTable tbls = fill_lookup_table();

    print_chess_board(&board);
    generate_position_moves(&board, white, &tbls);


    return 0;
}
