#include <stdio.h>
#include "chess_types.h"

LookupTable fill_lookup_table();
void print_chess_board(ChessBoard *board);
void parse_FEN(const char *FEN, ChessBoard *board);
void print_move(int move);
void play_move(int move, ChessBoard *board, const LookupTable *tbls, enum color side);
void generate_position_moves(const ChessBoard *board, enum color side, const LookupTable *tbls, struct move_list *list);
void sieve_moves(struct move_list *list, ChessBoard *board, const LookupTable *tbls, enum color side);
void print_move_list(const struct move_list *list);
void print_move(int move);
void play_move(int move, ChessBoard *board, const LookupTable *tbls, enum color side);

int main()
{
    ChessBoard board;
    parse_FEN("r2qk2r/1Ppbbp1p/p1n2np1/1p1pp3/3P4/1PN1PN2/2PBBPPP/1R1QK2R w Kkq", &board);
    LookupTable tbls = fill_lookup_table();
    struct move_list list;
    list.count = 0;

    /*print_chess_board(&board);

    int move = ENCODE_MOVE(d2, d3, w_pawn, 0, empty, 1, 1, 0);

    play_move(move, &board, &tbls, white);
    print_chess_board(&board);

    undo_move(move, &board, &tbls, white);
    print_chess_board(&board);*/

    //print_chess_board(&board);
    //generate_position_moves(&board, white, &tbls, &list);
    //sieve_moves(&list, &board, &tbls, white);
    //print_move_list(&list);

    int move = ENCODE_MOVE(e1, g1, w_king, empty, empty, 0 ,0, 1);
    print_move(move);
    print_chess_board(&board);
    play_move(move, &board, &tbls, white);
    print_chess_board(&board);
    return 0;
}
