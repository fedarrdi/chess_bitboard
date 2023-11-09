#include "chess_types.h"
#include "move_generation.h"
#include "piece_movement.h"
#include "position_hash_table.h"

int opening_table[12][64] =
        {
                /// white_pawn
                {
                        0, 0, 0, 0, 0, 0, 0, 0,
                        50, 50, 50, 50, 50, 50, 50, 50,
                        10, 10, 20, 30, 30, 20, 10, 10,
                        5, 5, 10, 25, 25, 10, 5, 5,
                        0, 0, 0, 20, 20, 0, 0, 0,
                        5, -5, -10, 0, 0, -10, -5, 5,
                        5, 10, 10, -20, -20, 10, 10, 5,
                        0, 0, 0, 0, 0, 0, 0, 0
                },
                ///white_knight
                {
                        -50, -40, -30, -30, -30, -30, -40, -50,
                        -40, -20, 0, 0, 0, 0, -20, -40,
                        -30, 0, 10, 15, 15, 10, 0, -30,
                        -30, 5, 15, 20, 20, 15, 5, -30,
                        -30, 0, 15, 20, 20, 15, 0, -30,
                        -30, 5, 10, 15, 15, 10, 5, -30,
                        -40, -20, 0, 5, 5, 0, -20, -40,
                        -50, -40, -30, -30, -30, -30, -40, -50
                },

                ///white bishop
                {
                        -20, -10, -10, -10, -10, -10, -10, -20,
                        -10, 0, 0, 0, 0, 0, 0, -10,
                        -10, 0, 5, 10, 10, 5, 0, -10,
                        -10, 5, 5, 10, 10, 5, 5, -10,
                        -10, 0, 10, 10, 10, 10, 0, -10,
                        -10, 10, 10, 10, 10, 10, 10, -10,
                        -10, 5, 0, 0, 0, 0, 5, -10,
                        -20, -10, -10, -10, -10, -10, -10, -20
                },
                ///white rook
                {
                        0, 0, 0, 0, 0, 0, 0, 0,
                        5, 10, 10, 10, 10, 10, 10, 5,
                        -5, 0, 0, 0, 0, 0, 0, -5,
                        -5, 0, 0, 0, 0, 0, 0, -5,
                        -5, 0, 0, 0, 0, 0, 0, -5,
                        -5, 0, 0, 0, 0, 0, 0, -5,
                        -5, 0, 0, 0, 0, 0, 0, -5,
                        0, 0, 0, 5, 5, 0, 0, 0
                },
                ///white queen
                {
                        -20, -10, -10, -5, -5, -10, -10, -20,
                        -10, 0, 0, 0, 0, 0, 0, -10,
                        -10, 0, 5, 5, 5, 5, 0, -10,
                        -5, 0, 5, 5, 5, 5, 0, -5,
                        0, 0, 5, 5, 5, 5, 0, -5,
                        -10, 5, 5, 5, 5, 5, 0, -10,
                        -10, 0, 5, 0, 0, 0, 0, -10,
                        -20, -10, -10, -5, -5, -10, -10, -20
                },
                ///white king
                {
                        -60, -70, -70, -80, -80, -70, -70, -60,
                        -50, -60, -60, -70, -70, -60, -60, -50,
                        -40, -50, -50, -60, -60, -50, -50, -40,
                        -30, -40, -40, -50, -50, -40, -40, -30,
                        -20, -30, -30, -40, -40, -30, -30, -20,
                        -10, -20, -20, -20, -20, -20, -20, -10,
                        20, 20, 0, 0, 0, 0, 20, 20,
                        20, 30, 10, 0, 0, 10, 30, 20
                },
                /// black pawn
                {
                        0, 0, 0, 0, 0, 0, 0, 0,
                        5, 10, 10, -20, -20, 10, 10, 5,
                        5, -5, -10, 0, 0, -10, -5, 5,
                        0, 0, 0, 20, 20, 0, 0, 0,
                        5, 5, 10, 25, 25, 10, 5, 5,
                        10, 10, 20, 30, 30, 20, 10, 10,
                        50, 50, 50, 50, 50, 50, 50, 50,
                        0, 0, 0, 0, 0, 0, 0, 0
                },
                /// black night
                {
                        -50, -40, -30, -30, -30, -30, -40, -50,
                        -40, -20, 0, 0, 0, 0, -20, -40,
                        -30, 0, 10, 15, 15, 10, 0, -30,
                        -30, 5, 15, 20, 20, 15, 5, -30,
                        -30, 0, 15, 20, 20, 15, 0, -30,
                        -30, 5, 10, 15, 15, 10, 5, -30,
                        -40, -20, 0, 5, 5, 0, -20, -40,
                        -50, -40, -30, -30, -30, -30, -40, -50
                },
                /// black bishop
                {
                        -20, -10, -10, -10, -10, -10, -10, -20,
                        -10, 5, 0, 0, 0, 0, 5, -10,
                        -10, 10, 10, 10, 10, 10, 10, -10,
                        -10, 0, 10, 10, 10, 10, 0, -10,
                        -10, 5, 5, 10, 10, 5, 5, -10,
                        -10, 0, 5, 10, 10, 5, 0, -10,
                        -10, 0, 0, 0, 0, 0, 0, -10,
                        -20, -10, -10, -10, -10, -10, -10, -20
                },
                ///black rook
                {
                        0, 0, 0, 5, 5, 0, 0, 0,
                        -5, 0, 0, 0, 0, 0, 0, -5,
                        -5, 0, 0, 0, 0, 0, 0, -5,
                        -5, 0, 0, 0, 0, 0, 0, -5,
                        -5, 0, 0, 0, 0, 0, 0, -5,
                        -5, 0, 0, 0, 0, 0, 0, -5,
                        5, 10, 10, 10, 10, 10, 10, 5,
                        0, 0, 0, 0, 0, 0, 0, 0
                },
                ///black queen
                {
                        20, -10, -10, -5, -5, -10, -10, -20,
                        -10, 0, 0, 0, 0, 0, 0, -10,
                        -10, 0, 5, 0, 0, 0, 0, -10,
                        -5, 0, 5, 5, 0, 0, 0, -5,
                        0, 0, 5, 5, 5, 5, 0, -5,
                        -10, 5, 0, 5, 5, 0, 0, -10,
                        -10, 0, 0, 0, 5, 0, 0, -10,
                        -20, -10, -10, -5, -5, -10, -10, -20
                },
                /// black king
                {
                        20, 20, 0, 0, 0, 0, 20, 20,
                        10, -20, -20, -20, -20, -20, -20, 10,
                        30, -30, -30, -40, -40, -30, -30, 30,
                        40, -40, -40, -50, -50, -40, -40, 40,
                        50, -50, -50, -60, -60, -50, -50, 50,
                        60, -60, -60, -70, -70, -60, -60, 60,
                        70, -70, -70, -80, -80, -70, -70, 70,
                        80, -80, -80, -90, -90, -80, -80, 80
                }
        };
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

long long positional_points(ChessBoard *board)
{
    long long res = 0;
    int from = (board->turn == white) ? w_pawn : b_pawn;
    int to = (board->turn == white) ? w_king : b_king;

    for(int i = from; i <= to; i++)
    {
        for (Bitboard piece_board = board->pieces[i]; piece_board;)
        {
            int square = get_f1bit_index(piece_board);
            POP_BIT(piece_board, square);
            res += opening_table[i][square];
        }
    }

    return res * ((board->turn == black) ? (-1) : 1);
}

long long evaluate_position(ChessBoard *board, const LookupTable *tbls, HashTable *t, Board_hash hash_key, unsigned curr_legal_move_count)
{
    int mate_factor = check_for_mate(board, tbls, curr_legal_move_count);
    if(mate_factor)
        return mate_factor;

    int path_factor = check_for_path(board, tbls, t, hash_key, curr_legal_move_count);
    long long score = count_pieces(board) + positional_points(board);
    return  score * path_factor;
}
