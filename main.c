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

int main()
{
    HashTable t;
    create_table(&t, 100);
    ChessBoard board = parse_FEN("r6k/6rP/4pR2/p2pQ1p1/3P2P1/8/1qpK4/5R2 w");
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();
   
    MoveList list = init_move_list();

    int depth = 4;
    enum color turn = white;

    print_chess_board(&board);

    for(int i = 0;i < 10;i++)
    {
        long long eval;
        int move;
        int a = 0, b = 0;

        if(turn == white)
        {
            board.turn = turn;
            if(min_max(&board, &tbls, &keys, &t, &move, &eval, depth, 0, 0) == false)
                a = 1;
            print_move(move);
            play_move(move, &board);
            
            if(a)
                return 0;
        }
        else
        {
            board.turn = turn;
            if(min_max(&board, &tbls, &keys, &t, &move, &eval, depth, 0, 0) == false)
                b = 1;
            
            print_move(move);
            play_move(move, &board);
            
            if(b)
                return 0;
        }

        print_chess_board(&board);
        turn = !turn;
    }

    return 0;
}
