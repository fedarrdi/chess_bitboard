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

///TO DO: Tables for piece activasion

int main()
{
    HashTable t;
    create_table(&t, 100);
    MoveList list = init_move_list();
    ChessBoard board = parse_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq");
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();

    int depth = 6;
    enum color turn = white;

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
