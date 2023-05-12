#include "chess_types.h"

#ifndef CHESS_BIT_BOARDS_GET_BEST_MOVE_H
#define CHESS_BIT_BOARDS_GET_BEST_MOVE_H

enum bool min_max(ChessBoard *board, LookupTable *tbls, Keys *keys, int *out_move, long long  *out_eval, int depth);

#endif //CHESS_BIT_BOARDS_GET_BEST_MOVE_H
