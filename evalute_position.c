#include "chess_types.h"
#include "move_generation.h"

/// zobrist hash board to check if current position had been seen 3 times then the game results in pat;
long long check_for_path(const ChessBoard *board, int curr_legal_move_count)
{
    return !!curr_legal_move_count;
}

long long evaluate_position(ChessBoard *board, int curr_legal_move_count, const LookupTable *tbls)
{
    return 0;
}
