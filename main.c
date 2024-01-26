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


int main()
{
    HashTable t;
    create_table(&t, 100);

    //ChessBoard board = parse_FEN("1k1r2n1/pPpnqpp1/4p2r/3pN2p/3P4/2PBP1P1/3N1PP1/1R2K2R w K");
    ChessBoard board = parse_FEN("QK6/8/8/8/8/5k2/8/8 w");

    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();
   
    MoveList list = init_move_list();
    
    print_chess_board(&board);
    
    int depth = 4;
    enum color turn = board.turn;
    for(int i = 0;i < 1;i++)
    {
        long long eval;
        int move;
        board.turn == white ? printf("WHITE\n") : printf("BLACK\n");
        
        min_max(&board, &tbls, &keys, &t, &move, &eval, depth, LLONG_MIN, LLONG_MAX, depth);
        
        printf("===============================================================================\n");
        print_move(move);
        play_move(move, &board);
        printf("EVALUATION: %lli", eval);            

        print_chess_board(&board);
        board.turn  = !board.turn;

    }
    
    return 0;
}
