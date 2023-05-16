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
    ChessBoard board = parse_FEN("8/8/8/3k4/7R/Q7/PP5B/KP6 w");
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();



    for(enum color turn = white; true ; turn = !turn)
    {
        print_chess_board(&board);
        if(turn == white)
        {
            int out_move = -1;
            long long out_eval = -1;
            if (min_max(&board, &tbls, &keys, &out_move, &out_eval, 2)) {
                play_move(out_move, &board);
                print_move(out_move);
            } else {
                break;
            }
        }
        else
        {
            player_make_move(&board, turn, &tbls);
        }

    }


    return 0;
}
