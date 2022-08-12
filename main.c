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
void sieve_moves(struct move_list *list, ChessBoard *board, const LookupTable *tbls, enum color side);
void print_move_list(const struct move_list *list);
void print_move(int move);
/// Sieve moves check prevention doesn't work need to FIX!!!
int main()
{
    ChessBoard board;
    parse_FEN("8/8/8/8/8/8/4nnn1/4nKn1 w", &board);
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
    sieve_moves(&list, &board, &tbls, white);
    print_move_list(&list);


    return 0;
}
