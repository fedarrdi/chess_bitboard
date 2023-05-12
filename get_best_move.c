#include <string.h>
#include <stdio.h>
#include "chess_types.h"
#include "move_generation.h"
#include "evalute_position.h"
#include "make_move.h"
#include "zobrist_hashing.h"

enum bool min_max(ChessBoard *board, LookupTable *tbls, Keys *keys, int *out_move, long long  *out_eval, int depth)
{
    struct move_list list;
    list.count = 0;

    ///generate position moves
    generate_position_moves(board,  tbls, &list);
    sieve_moves(&list, board, tbls);

    ///current position hash key
    Board_hash hash_key = get_bord_hash(board, keys);

    int best_move = -1;
    long long curr_eval, best_eval = evaluate_position(board, tbls, hash_key, list.count);

    for(int move_index = 0; move_index < list.count; move_index ++)
    {
        /// copy board before the move is done
        Bitboard pieces[12], occupied[3];
        memcpy(pieces, board->pieces, sizeof(pieces[1])*12);
        memcpy(occupied, board->occupied, sizeof (occupied[1]) * 3);

        play_move(list.moves[move_index], board);

        /// hash key after the played move
        Board_hash new_key = get_bord_hash(board, keys);

        ///calculate new position evaluation
        curr_eval = evaluate_position(board, tbls, new_key, list.count);

        ///if the current position is mate no more need to search
        if(curr_eval >= CHECK_MATE_V || curr_eval <= -CHECK_MATE_V)
        {
            best_move = list.moves[move_index];
            best_eval = curr_eval;
            break;
        }

        /// going one depth further
        if(depth)
            min_max(board, tbls, keys, out_move, &curr_eval, depth - 1);

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