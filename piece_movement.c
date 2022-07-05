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
            moves = m1 | m2 | m3 | m4 | m5 | m6 | m7 | m8;

    return moves  & ~own_side;
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
            moves = m1 | m2 | m3 | m4 | m5 | m6 | m7 | m8;

    return moves & ~own_side;
}

Bitboard white_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls)
{
    Bitboard all_pieces = own_side | enemy_side;
    Bitboard white_pawn_one_step  = (pawn_pos >> 8) & ~all_pieces,
            white_pawn_two_step  = ((white_pawn_one_step & tbls->MaskRank[RANK_3]) >> 8) & ~all_pieces,
            white_pawn_left_attack = (pawn_pos >> 9) & tbls->ClearFile[FILE_H] & enemy_side,
            white_pawn_right_attack = (pawn_pos >> 7) & tbls->ClearFile[FILE_A] & enemy_side,
            moves = white_pawn_one_step | white_pawn_two_step | white_pawn_left_attack | white_pawn_right_attack;

    return moves;
}

Bitboard black_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls)
{
    Bitboard all_pieces = own_side | enemy_side;
    Bitboard black_pawn_one_step  = (pawn_pos << 8) & ~all_pieces,
            black_pawn_two_step  = ((black_pawn_one_step & tbls->MaskRank[RANK_6]) << 8) & ~all_pieces,
            black_pawn_left_attack = (pawn_pos << 9) & tbls->ClearFile[FILE_A] & enemy_side,
            black_pawn_right_attack = (pawn_pos << 7) & tbls->ClearFile[FILE_H] & enemy_side,
            moves = black_pawn_one_step | black_pawn_two_step | black_pawn_left_attack | black_pawn_right_attack;

    return moves;
}