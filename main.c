#include <stdio.h>
#include "chess_types.h"
#include "evalute_position.h"
#include "get_best_move.h"
#include "init_functions.h"
#include "make_move.h"
#include "move_generation.h"
#include "piece_movement.h"
#include "player_interface.h"
#include "zobrist_hashing.h"

///TO DO: add path, and mate check if path and math positions are being found by the min max algorithm

int main()
{

    MoveList list = init_move_list();
    ChessBoard board = parse_FEN("rnbqkbnr/ppppp2p/5p2/6p1/8/4P3/PPPPBPPP/RNBQK1NR w KQkq");
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();


    int out_move = -1;
    long long out_eval = -1;
    if(min_max(&board, &tbls, &keys, &out_move, &out_eval, 2))
    {
        print_chess_board(&board);
        print_move(out_move);
    }

   /* print_chess_board(&board);
    Bitboard hash = get_bord_hash(&board, &keys);
    printf("%llu\n", hash);
    generate_position_moves(&board, &tbls, &list);*/


    return 0;
}
