#include "chess_types.h"

#ifndef CHESS_BIT_BOARDS_MOVE_GENERATION_H
#define CHESS_BIT_BOARDS_MOVE_GENERATION_H

int get_f1bit_index(Bitboard board);
Bitboard get_piece_move(enum piece piece, Bitboard pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard generate_all_attacks(const ChessBoard *board, const LookupTable *tbls);
void generate_position_moves(ChessBoard *board, const LookupTable *tbls, MoveList *list);
void sieve_moves(MoveList *list, ChessBoard *board, const LookupTable *tbls);
void move_ordering_by_capture(MoveList *list);
enum bool is_king_checked(ChessBoard *board, const LookupTable *tbls);

#endif //CHESS_BIT_BOARDS_MOVE_GENERATION_H
