#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard);
LookupTable fill_lookup_table();
void print_chess_board(ChessBoard *board);
void parse_FEN(const char *FEN, ChessBoard *board);
void print_move(int move);
void play_move(int move, ChessBoard *board, const LookupTable *tbls, enum color side);
void undo_move(int move, ChessBoard *board, const LookupTable *tbls, enum color side);
void generate_position_moves(const ChessBoard *board, enum color side, const LookupTable *tbls, struct move_list *list);
void print_move_list(const struct move_list *list);

int main()
{
    ChessBoard board;
    parse_FEN("rn1qk2r/pb1pbppp/1p2pn2/8/2p5/PN1P1NPP/1PPBPPB1/R2QK2R b KQkq", &board);
    LookupTable tbls = fill_lookup_table();
    struct move_list list;
    list.count = 0;

    /*print_chess_board(&board);

    int move = ENCODE_MOVE(d2, d3, w_pawn, 0, empty, 1, 1, 0);

    play_move(move, &board, &tbls, white);
    print_chess_board(&board);

    undo_move(move, &board, &tbls, white);
    print_chess_board(&board);*/

    print_chess_board(&board);
    generate_position_moves(&board, white, &tbls, &list);
    print_move_list(&list);

    return 0;
}
