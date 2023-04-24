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

int main()
{
    MoveList list;
    list.count = 0;

    ChessBoard board = parse_FEN("rnbqkbnr/pppp1pp1/7p/3Pp3/8/8/PPP1PPPP/RNBQKBNR w KQkq e6");
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();

    print_chess_board(&board);
    Bitboard hash = get_bord_hash(&board, &keys);
    printf("%llu\n", hash);
    generate_position_moves(&board, &tbls, &list);

    return 0;
}
