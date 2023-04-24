
#include "chess_types.h"

#ifndef CHESS_BIT_BOARDS_EVALUTE_POSITION_H
#define CHESS_BIT_BOARDS_EVALUTE_POSITION_H

long long evaluate_position(ChessBoard *board, int curr_legal_move_count, const LookupTable *tbls);

#endif //CHESS_BIT_BOARDS_EVALUTE_POSITION_H
