
#include "chess_types.h"

#ifndef CHESS_BIT_BOARDS_EVALUTE_POSITION_H
#define CHESS_BIT_BOARDS_EVALUTE_POSITION_H

long long evaluate_position(ChessBoard *board, const LookupTable *tbls, Board_hash hash_key, unsigned curr_legal_move_count);

#endif //CHESS_BIT_BOARDS_EVALUTE_POSITION_H
