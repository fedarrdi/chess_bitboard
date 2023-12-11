#include <stdio.h>
#include <limits.h>
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

int main()///error unvalid moves
{
    for(int depth = 0;depth <  6;depth ++)
    {

    HashTable t;
    create_table(&t, 100);

    ChessBoard board = parse_FEN("8/6P1/5K2/1k6/8/8/8/8 w");
    
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();
   
    MoveList list = init_move_list();
    
    print_chess_board(&board);
    enum color turn = board.turn;
    for(int i = 0;i < 1;i++)
    {
        long long eval;
        int move;
        board.turn == white ? printf("WHITE\n") : printf("BLACK\n");

        min_max(&board, &tbls, &keys, &t, &move, &eval, depth, LLONG_MIN, LLONG_MAX, depth);
            
        print_move(move);
        play_move(move, &board);
        printf("EVALUATION: %lli", eval);            

        print_chess_board(&board);
        board.turn  = !board.turn;

    }
    }
    return 0;
}
