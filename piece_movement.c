#include "chess_types.h"


Bitboard king_move(Bitboard king_pos, Bitboard allay_piece, LookupTable *tbls)
{
    Bitboard m1 = (king_pos >> 8),
            m2 = (king_pos << 8),
            m3 = ((king_pos >> 7) & tbls->ClearFile[FILE_A]),
            m4 = ((king_pos << 7) & tbls->ClearFile[FILE_H]),
            m5 = ((king_pos >> 1) & tbls->ClearFile[FILE_H]),
            m6 = ((king_pos << 1) & tbls->ClearFile[FILE_A]),
            m7 = ((king_pos >> 9) & tbls->ClearFile[FILE_H]),
            m8 = ((king_pos << 9) & tbls->ClearFile[FILE_A]);

    return m1 | m2 | m3 | m4 | m5 | m6 | m7 | m8;
}