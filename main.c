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
    ChessBoard board = parse_FEN("r1bqk2r/2p2ppp/1pnb1n2/pB1pp3/3PP3/1P3N1P/PBP2PP1/RN1QK2R b KQkq");
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();
    
/*  generate_position_moves(&board, &tbls, &list);
    sieve_moves(&list, &board, &tbls);
    move_ordering_by_capture(&list);
    print_move_list(&list); */

    int depth = 8;
    enum color turn = white;

    for(int i = 0;i < 10;i++)
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
