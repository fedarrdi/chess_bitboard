#include "chess_types.h"

Bitboard king_move(Bitboard king_pos, Bitboard own_side, LookupTable *tbls)
{
    Bitboard m1 = (king_pos >> 8),
            m2 = (king_pos << 8),
            m3 = ((king_pos >> 7) & tbls->ClearFile[FILE_A]),
            m4 = ((king_pos << 7) & tbls->ClearFile[FILE_H]),
            m5 = ((king_pos >> 1) & tbls->ClearFile[FILE_H]),
            m6 = ((king_pos << 1) & tbls->ClearFile[FILE_A]),
            m7 = ((king_pos >> 9) & tbls->ClearFile[FILE_H]),
            m8 = ((king_pos << 9) & tbls->ClearFile[FILE_A]),
            move_board = m1 | m2 | m3 | m4 | m5 | m6 | m7 | m8;

    return move_board  & ~own_side;
}

Bitboard knight_move(Bitboard knight_pos, Bitboard own_side, LookupTable *tbls)
{
    Bitboard m1 = (knight_pos >> 6) & tbls->ClearFile[FILE_A] & tbls->ClearFile[FILE_B],
            m2 = (knight_pos >> 10) & tbls->ClearFile[FILE_H] & tbls->ClearFile[FILE_G],
            m3 = (knight_pos >> 15) & tbls->ClearFile[FILE_A],
            m4 = (knight_pos >> 17) & tbls->ClearFile[FILE_H],
            m5 = (knight_pos << 6) & tbls->ClearFile[FILE_H] & tbls->ClearFile[FILE_G],
            m6 = (knight_pos << 10) & tbls->ClearFile[FILE_A] & tbls->ClearFile[FILE_B] ,
            m7 = (knight_pos << 15) & tbls->ClearFile[FILE_H],
            m8 = (knight_pos << 17) & tbls->ClearFile[FILE_A],
            move_board = m1 | m2 | m3 | m4 | m5 | m6 | m7 | m8;

    return move_board & ~own_side;
}

Bitboard white_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls)
{
    Bitboard m1 = (pawn_pos >> 8) & ~own_side;
}