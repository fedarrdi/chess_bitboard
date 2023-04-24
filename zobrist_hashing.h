//
// Created by fedar on 4/24/2023.
//
#include "chess_types.h"

#ifndef CHESS_BIT_BOARDS_ZOBRIST_HASHING_H
#define CHESS_BIT_BOARDS_ZOBRIST_HASHING_H

struct random_keys init_random_keys();
Bitboard get_bord_hash(ChessBoard *board, Keys *keys);


#endif //CHESS_BIT_BOARDS_ZOBRIST_HASHING_H
