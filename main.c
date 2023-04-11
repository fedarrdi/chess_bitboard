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

    ChessBoard board = parse_FEN("r2qkb1r/pp2nppp/3p4/2pNN1B1/2BnP3/3P4/PPP2PPP/R2bK2R w KQkq");
    LookupTable tbls = fill_lookup_table();
    print_chess_board(&board);

    long long eval;
    int move;

    if(min_max(&board, &tbls, &move, &eval, 0))
    {
        print_move(move);
        play_move(move, &board, &tbls);
    }

    print_chess_board(&board);

    return 0;
}
