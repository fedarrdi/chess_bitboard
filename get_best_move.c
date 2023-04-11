#include "chess_types.h"
#include <string.h>
#include <stdio.h>
#include "move_generation.h"
#include "evalute_position.h"
#include "make_move.h"

enum bool min_max(ChessBoard *board, const LookupTable *tbls, int *out_move, long long  *out_eval, int depth)
{
    struct move_list list;
    list.count = 0;

    ///generate position moves
    generate_position_moves(board,  tbls, &list);
    sieve_moves(&list, board, tbls);

    int best_move = -1;
    long long curr_eval, best_eval = evaluate_position(board, list.count, tbls);

    for(int move_index = 0; move_index < list.count; move_index ++)
    {
        /// copy board before the move is done
        Bitboard pieces[12], occupied[3];
        memcpy(pieces, board->pieces, sizeof(pieces[1])*12);
        memcpy(occupied, board->occupied, sizeof (occupied[1]) * 3);

        play_move(list.moves[move_index], board, tbls);

        ///calculate new position evaluation
        curr_eval = evaluate_position(board, list.count, tbls);

        /// going one depth further
        if(depth)
            min_max(board, tbls,  out_move, &curr_eval, depth - 1);

        ///if the current position is better then the current best update
        if((board->turn == white && best_eval <= curr_eval) || (board->turn == black && best_eval >= curr_eval))
        {
            printf("move index: %d\n", move_index);

            best_eval = curr_eval;
            best_move = list.moves[move_index];
        }
        /// undo the move
        memcpy(board->pieces, pieces, sizeof(pieces[1])*12);
        memcpy(board->occupied, occupied, sizeof (occupied[1]) * 3);
    }

    if(best_move == -1)
        return false;

    *out_move = best_move;
    *out_eval = best_eval;
    return true;
}