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
    HashTable t;
    create_table(&t, 100);

    ChessBoard board = parse_FEN("2kr2n1/pPpnqpp1/4p2r/3pN2p/3P4/2PBP1P1/3N1PP1/1R2K2R b K");
    
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();
   
    MoveList list = init_move_list();
    
    int depth = 2; 
    print_chess_board(&board);
    enum color turn = board.turn;
    for(int i = 0;i < 3;i++)
    {
        long long eval;
        int move;
        board.turn == white ? printf("WHITE\n") : printf("BLACK\n");

        min_max(&board, &tbls, &keys, &t, &move, &eval, depth, LLONG_MIN, LLONG_MAX);
            
        print_move(move);
        play_move(move, &board);
        printf("EVALUATION: %lli", eval);            

        print_chess_board(&board);
        board.turn  = !board.turn;

    }
    
    return 0;
}
