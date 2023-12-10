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

int main()///error unvalid moves
{
    HashTable t;
    create_table(&t, 100);
    ChessBoard board = parse_FEN("1k6/6KP/8/8/8/8/8/8 w");
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();
   
    MoveList list = init_move_list();
    
    int depth = 2; 
    long long eval;
    int move;

    enum color turn = board.turn;
    for(int i = 0;i < 1;i++)
    {
        long long eval;
        int move;
        int a = 0, b = 0;

        if(turn == white)
        {
            printf("WHITE\n");
            board.turn = turn;
            if(min_max(&board, &tbls, &keys, &t, &move, &eval, depth, 0, 0) == false)
                a = 1;
            print_move(move);
            play_move(move, &board);
            printf("EVALUATION: %lli", eval);            
        }
        else
        {
            printf("BLACK\n");
            board.turn = turn;
            if(min_max(&board, &tbls, &keys, &t, &move, &eval, depth, 0, 0) == false)
                b = 1;
            
            print_move(move);
            play_move(move, &board);
            printf("EVALUATION: %lli", eval);            
        }

        print_chess_board(&board);
        if(a || b)
            return 0;
        turn = !turn;
        }
    return 0;
}
