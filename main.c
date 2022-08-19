#include <stdio.h>
#include "chess_types.h"

ChessBoard parse_FEN(const char *FEN);
LookupTable fill_lookup_table();
void print_chess_board(ChessBoard *board);
enum bool min_max(ChessBoard *board, const LookupTable *tbls, int *out_move, long long  *out_eval, int depth);
void print_move(int move);
void generate_position_moves(const ChessBoard *board, const LookupTable *tbls, struct move_list *list);
void sieve_moves(struct move_list *list, ChessBoard *board, const LookupTable *tbls);
enum bool min_max(ChessBoard *board, const LookupTable *tbls, int *out_move, long long  *out_eval, int depth);
void play_move(int move, ChessBoard *board, const LookupTable *tbls);


int main()
{
    struct move_list list;
    list.count = 0;

    ChessBoard board = parse_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
    LookupTable tbls = fill_lookup_table();
    print_chess_board(&board);

    long long eval;
    int move;
    if(min_max(&board, &tbls, &move, &eval, 0))
    {
        print_move(move);
        play_move(move, &board, &tbls);
    }

    print_chess_board(&board);

    return 0;
}
