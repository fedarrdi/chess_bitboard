#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
void print_chess_board(ChessBoard *board);
void parse_FEN(const char *FEN, ChessBoard *board);
void print_move(int move);
void play_move(int move, ChessBoard *board, const LookupTable *tbls, enum color side);
void undo_move(int move, ChessBoard *board, const LookupTable *tbls, enum color side);

int main()
{
    ChessBoard board;
    parse_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq", &board);
    LookupTable tbls = fill_lookup_table();

    print_chess_board(&board);

    int move = ENCODE_MOVE(d2, d3, w_pawn, 0, empty, 1, 1, 0);

    play_move(move, &board, &tbls, white);
    print_chess_board(&board);

    undo_move(move, &board, &tbls, white);
    print_chess_board(&board);

    return 0;
}
