#include "chess_types.h"

#ifndef CHESS_BIT_BOARDS_PIECE_MOVEMENT_H
#define CHESS_BIT_BOARDS_PIECE_MOVEMENT_H

Bitboard king_move(Bitboard king_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard knight_move(Bitboard knight_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard white_pawn_attacks(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard white_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard black_pawn_attacks(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard black_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard bishop_move(Bitboard bishop_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard rook_move(Bitboard rook_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard queen_move(Bitboard queen_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);


#endif //CHESS_BIT_BOARDS_PIECE_MOVEMENT_H
