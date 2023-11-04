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
#include "position_hash_table.h"

///TO DO: add path, and mate check if path and math positions are being found by the min max algorithm

int main()
{

    HashTable t;
    MoveList list = init_move_list();
    ChessBoard board = parse_FEN("6K1/2PQ4/6pq/3p3P/2pB1b1p/8/4r2k/1R6 b ");
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();

    print_chess_board(&board);


    int move, depth = 6;
    long long eval;
    min_max(&board, &tbls, &keys, &t, &move, &eval, depth);
    print_move(move);



    return 0;
}