#include "chess_types.h"

#ifndef CHESS_BIT_BOARDS_PLAYER_INTERFACE_H
#define CHESS_BIT_BOARDS_PLAYER_INTERFACE_H

void print_chess_board(ChessBoard *board);
void print_move(int move);
void player_make_move(ChessBoard *board, enum color side, const LookupTable *tbls);
void print_move_list(const struct move_list *list);

#endif //CHESS_BIT_BOARDS_PLAYER_INTERFACE_H
