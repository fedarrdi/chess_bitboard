#include "chess_types.h"
#include "move_generation.h"
#include "piece_movement.h"

/// zobrist hash board to check if current position had been seen 3 times then the game results in pat;
long long check_for_path(ChessBoard *board, Board_hash hash_key, int curr_legal_move_count)
{
    return !!curr_legal_move_count;
}

long long check_for_mate(ChessBoard *board, const LookupTable *tbls, unsigned curr_legal_moves_count)
{
    board->turn = !board->turn;
    if(!curr_legal_moves_count && is_king_checked(board, tbls))
    {
        board->turn = !board->turn;
        return CHECK_MATE_V * ( (board->turn == white) ? (1) : (-1) );
    }

    board->turn = !board->turn;
    return 0;
}

long long evaluate_position(ChessBoard *board, const LookupTable *tbls, Board_hash hash_key, unsigned curr_legal_move_count)
{
    return check_for_mate(board, tbls, curr_legal_move_count);
}
