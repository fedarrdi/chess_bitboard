#include "chess_types.h"
#include "move_generation.h"
#include "piece_movement.h"
#include "position_hash_table.h"

int check_for_path(ChessBoard *board, const LookupTable *tbls, HashTable *t, Board_hash hash_key, unsigned curr_legal_moves_count)
{
    return ((position_occurrences(t, hash_key) == 3) ? 0 : 1) || (!curr_legal_moves_count && !is_king_checked(board, tbls));
}

int check_for_mate(ChessBoard *board, const LookupTable *tbls, unsigned curr_legal_moves_count)
{
    if(!curr_legal_moves_count && is_king_checked(board, tbls))
        return 10 * CHECK_MATE_V * ( (board->turn == white) ? (-1) : (1) ); /// if white are mate then black wins

    return 0;
}

int piece_weight[13] = {10, 50, 50, 100, 200, 1000000, -10, -50, -50, -100, -200, -1000000, 0};

long long count_pieces(ChessBoard *board)
{
    long long res = 0;
    for (int i = w_pawn; i <= b_king; i++)
        for(Bitboard piece_board = board->pieces[i] ;piece_board; POP_BIT(piece_board, get_f1bit_index(piece_board)))
            res += piece_weight[i];

    return res;
}

long long evaluate_position(ChessBoard *board, const LookupTable *tbls, HashTable *t, Board_hash hash_key, unsigned curr_legal_move_count)
{
    int mate_factor = check_for_mate(board, tbls, curr_legal_move_count);
    if(mate_factor)
        return mate_factor;

    int path_factor = check_for_path(board, tbls, t, hash_key, curr_legal_move_count);
    long long pieces = count_pieces(board);
    return  pieces * path_factor; /// if the position is path the result of the position will be multiplate by 0
}
