#include "chess_types.h"
#include "move_generation.h"

/// zobrist hash board to check if current position had been seen 3 times then the game results in pat;
long long check_for_path(const ChessBoard *board, int curr_legal_move_count)
{
    return !!curr_legal_move_count;
}

unsigned count_number_bits(Bitboard number)
{
    unsigned cnt = 0;
    for(int pos = 0;pos < 64;pos++)
        cnt += number & (1 << pos);
    return cnt;
}
  
long long eval_pawns(const ChessBoard *board, const LookupTable *tbls)
{
    Bitboard pawn_board = board->turn == white ? board->pieces[w_pawn] : board->pieces[b_pawn];
    Bitboard raw_pawn_attacks = board->turn == white ?
                            (((pawn_board >> 7) & (pawn_board >> 9)) & tbls->ClearFile[FILE_H]) :
                            ((pawn_board << 7) & (pawn_board << 9)) & tbls->ClearFile[FILE_A];

    Bitboard enemy_piece_attacked = raw_pawn_attacks & board->pieces[!board->turn];
    Bitboard own_piece_defended = raw_pawn_attacks & board->pieces[board->turn];
    Bitboard attacked_empty_squares = raw_pawn_attacks - enemy_piece_attacked - own_piece_defended;

    return count_number_bits(enemy_piece_attacked) * 3 + count_number_bits(own_piece_defended) * 2 + count_number_bits(attacked_empty_squares);
}

long long check_for_mate(ChessBoard *board, const LookupTable *tbls, int curr_legal_move_count)
{
    board->turn = !board->turn;
    Bitboard enemy_attacks = generate_all_attacks(board, tbls);
    board->turn = !board->turn;
    enum piece king = board->turn ? w_king : black;
    if(!curr_legal_move_count && board->pieces[king] & enemy_attacks)
        return MAX_LL;
}

long long evaluate_position(ChessBoard *board, int curr_legal_move_count, const LookupTable *tbls)
{
    long long evaluation = 0;

    evaluation += eval_pawns(board, tbls) + check_for_mate(board, tbls, curr_legal_move_count);

    return evaluation * check_for_path(board, curr_legal_move_count);
}
