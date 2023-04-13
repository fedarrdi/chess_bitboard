#include <stdio.h>
#include "chess_types.h"
#include "evalute_position.h"
#include "get_best_move.h"
#include "init_functions.h"
#include "make_move.h"
#include "move_generation.h"
#include "piece_movement.h"
#include "player_interface.h"

int main()
{
    struct move_list list;
    list.count = 0;

    ChessBoard board = parse_FEN("8/8/8/3Pp3/8/8/8/8 w 0000 e6");
    LookupTable tbls = fill_lookup_table();
    print_chess_board(&board);

    generate_position_moves(&board, &tbls, &list);

    /*long long eval;
    int move;

    if(min_max(&board, &tbls, &move, &eval, 0))
    {
        print_move(move);
        play_move(move, &board, &tbls);
    }

    print_chess_board(&board);*/

    return 0;
}
