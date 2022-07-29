#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
void print_chess_board(ChessBoard *board);
void generate_position_moves(ChessBoard *board, enum color side, const LookupTable *tbls);
void parse_FEN(const char *FEN, ChessBoard *board);

int main()
{
    ChessBoard board;
    parse_FEN("rnbqk1nr/pppp1ppp/4p3/8/1b6/3P4/PPPBPPPP/RN1QKBNR w KQkq", &board);
    LookupTable tbls = fill_lookup_table();

    print_chess_board(&board);
    generate_position_moves(&board, white, &tbls);
    int move = ENCODE_MOVE(a1, a2, w_rook, 0, 0, 0, 0, 0);

    return 0;
}
