//
// Created by fedar on 7/7/2022.
//

#ifndef CHESS_BIT_BOARDS_PLAYER_TYPES_H
#define CHESS_BIT_BOARDS_PLAYER_TYPES_H

typedef struct position {int x, y;} Position;
typedef struct move {struct position from, to;} Move;
enum bool {false, true};

#endif //CHESS_BIT_BOARDS_PLAYER_TYPES_H
