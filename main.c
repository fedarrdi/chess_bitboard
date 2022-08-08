#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
void print_chess_board(ChessBoard *board);
void parse_FEN(const char *FEN, ChessBoard *board);
void print_move(int move);
void player_make_move(ChessBoard *board, enum color side, const LookupTable *tbls);

int main()
{
    ChessBoard board;
    parse_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq", &board);
    LookupTable tbls = fill_lookup_table();

    print_chess_board(&board);
  //  generate_position_moves(&board, white, &tbls);
  //  int move = ENCODE_MOVE(a1, a2, w_rook, w_queen, w_king, 0, 0, 0);
  //  print_move(move);

    for(int i = 0;i < 10;i++)
    {
        player_make_move(&board, white, &tbls);
        print_chess_board(&board);
    }
    return 0;
}
