#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
void print_chess_board(ChessBoard *board);
ChessBoard fill_chess_board();
void generate_position_moves(const ChessBoard *board, enum color side, const LookupTable *tbls);

int main()
{
    ChessBoard board = fill_chess_board();
    LookupTable tbls = fill_lookup_table();

    print_chess_board(&board);
    print_bitboard(board.occupied[both]);
    print_bitboard(tbls.MaskRank[RANK_8]);
    generate_position_moves(&board, white, &tbls);
    return 0;
}
