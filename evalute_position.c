#include "chess_types.h"
#include "move_generation.h"
#include "piece_movement.h"
#include "position_hash_table.h"

/// zobrist hash board to check if current position had been seen 3 times then the game results in pat;
long long check_for_path(ChessBoard *board, const LookupTable *tbls, HashTable *t, Board_hash hash_key)
{
    return (position_occurrences(t, hash_key) == 3) ? 0 : 1;
}

long long check_for_mate(ChessBoard *board, const LookupTable *tbls, unsigned curr_legal_moves_count)
{
    if(!curr_legal_moves_count && is_king_checked(board, tbls))
    {
        return 10 * CHECK_MATE_V * ( (board->turn == white) ? (-1) : (1) ); /// if white are mate then black wins
    }

    return 0;
}

long long evaluate_position(ChessBoard *board, const LookupTable *tbls, HashTable *t, Board_hash hash_key, unsigned curr_legal_move_count)
{
    return check_for_mate(board, tbls, curr_legal_move_count) * check_for_path(board, tbls, t, hash_key);
}
