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
    ChessBoard board = parse_FEN("2rr3k/p4p1p/1p1B4/8/3n2R1/5p1q/8/6K1 w");
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();
   
    MoveList list = init_move_list();

    int depth = 4;
    enum color turn = white;

    print_chess_board(&board);

    for(int i = 0;i < 4;i++)
    {
        long long eval;
        int move;

        if(turn == white)
        {
            board.turn = turn;
            min_max(&board, &tbls, &keys, &t, &move, &eval, depth, 0, 0);
            print_move(move);
            play_move(move, &board);
        }
        else
        {
            board.turn = turn;
            min_max(&board, &tbls, &keys, &t, &move, &eval, depth, 0, 0);
            print_move(move);
            play_move(move, &board);
        }

        print_chess_board(&board);
        turn = !turn;
    }

    return 0;
}
