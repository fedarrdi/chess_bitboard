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
    parse_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Kkq", &board);
    LookupTable tbls = fill_lookup_table();

    print_chess_board(&board);
    generate_position_moves(&board, white, &tbls);


    return 0;
}
