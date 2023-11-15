#include<stdio.h>
#include <string.h>
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

enum bool min_max(ChessBoard *board, const LookupTable *tbls, const Keys *keys, HashTable *t, int *out_move, long long  *out_eval, int depth, int alpha, int beta)
{
    MoveList list = init_move_list();

    ///generate position moves
    generate_position_moves(board,  tbls, &list);
    sieve_moves(&list, board, tbls);
    move_ordering_by_capture(&list);

    ///current position hash key
    Board_hash hash_key = get_bord_hash(board, keys);

    int best_move = -1;
    long long curr_eval, best_eval = (board->turn == white) ? -CHECK_MATE_V : CHECK_MATE_V;

    ///if the position is mate and there are no moves
    *out_eval = best_eval;

    for(int move_index = 0; move_index < list.count; move_index ++)
    {
        /// copy board before the move is done
        Bitboard pieces[12], occupied[3];
        memcpy(pieces, board->pieces, sizeof(pieces[1])*12);
        memcpy(occupied, board->occupied, sizeof (occupied[1]) * 3);

        play_move(list.moves[move_index], board); /// when move is made in the main function insert_item() need ti be called

        /// hash key after the played move
        Board_hash new_key = get_bord_hash(board, keys);
        insert_item(t, new_key);

        ///calculate new position evaluation
        curr_eval = evaluate_position(board, tbls, t, new_key, list.count, list.moves[move_index]);

        ///change the turn
        board->turn = !board->turn;

        /// going one depth further
        if(depth)
            min_max(board, tbls, keys, t, out_move, &curr_eval, depth - 1, alpha, beta);

        ///set to original
        board->turn = !board->turn;

        ///if the current position is mate no more need to search
        if(curr_eval >= CHECK_MATE_V || curr_eval <= -CHECK_MATE_V)
        {
            /// undo the move
            memcpy(board->pieces, pieces, sizeof(pieces[1])*12);
            memcpy(board->occupied, occupied, sizeof (occupied[1]) * 3);
            /// removing the position if it is seen for the first time, or decresing the seen counter

            remove_item(t, new_key);

            best_move = list.moves[move_index];
            best_eval = curr_eval;
            break;
        }

        ///if the current position is better then the current best update
        if((board->turn == white && best_eval <= curr_eval) || (board->turn == black && best_eval >= curr_eval))
        {
            (board->turn) ? (alpha = curr_eval) : (beta = curr_eval);
            best_eval = curr_eval;
            best_move = list.moves[move_index];
        }

        /// undo the move
        memcpy(board->pieces, pieces, sizeof(pieces[1])*12);
        memcpy(board->occupied, occupied, sizeof (occupied[1]) * 3);

        /// removing the position if it is seen for the first time, or decresing the seen counter
        remove_item(t, new_key);

        if(beta <= alpha) break;
    }

    if(best_move == -1)
        return false;

    *out_move = best_move;
    *out_eval = best_eval;
    return true;
}
