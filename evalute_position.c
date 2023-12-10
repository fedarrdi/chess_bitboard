#include <stdio.h>
#include "chess_types.h"
#include "move_generation.h"
#include "piece_movement.h"
#include "position_hash_table.h"
#include "init_functions.h"

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
                        0, 0, 0, 40, 40, 0, 0, 0,
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
                        20, 30, 10, 0, 0, 10, 30, 20,
                        20, 20, 0, 0, 0, 0, 20, 20,
                        -10, -20, -20, -20, -20, -20, -20, -10,
                        -20, -30, -30, -40, -40, -30, -30, -20,
                        -30, -40, -40, -50, -50, -40, -40, -30,
                        -40, -50, -50, -60, -60, -50, -50, -40,
                        -50, -60, -60, -70, -70, -60, -60, -50,
                        -60, -70, -70, -80, -80, -70, -70, -60
                }
        };

int piece_weight[13] = {30, 100, 100, 200, 600, 0, -30, -100, -100, -200, -600, 0, 0};

long long count_pieces(const ChessBoard *board)
{
    long long res = 0;
    for (int i = w_pawn; i <= b_king; i++)
        for(Bitboard piece_board = board->pieces[i] ;piece_board; POP_BIT(piece_board, get_f1bit_index(piece_board)))
            res += piece_weight[i];
    return res;
}

long long move_positioning(const ChessBoard *board, int move)
{
    int piece = DECODE_MOVE_PIECE(move);
    int square = DECODE_MOVE_TO(move);
    return opening_table[piece][square] * ((board->turn == black) ? (-1) : 1);
}

int check_for_mate_or_path(ChessBoard *board, const LookupTable *tbls, HashTable *t, Board_hash hash_key) // 0 for nothing 1 for mate 2 for path 
{

    Bitboard attacks = generate_all_attacks(board, tbls);
    board->turn = !board->turn;

    MoveList list = init_move_list();
    generate_position_moves(board, tbls, &list);
    sieve_moves(&list, board, tbls);
   

    enum piece king = (board->turn == white) ? (w_king) : (b_king);
    Bitboard king_position = board->pieces[king];

    board->turn = !board->turn;
    
    if(!list.count && (king_position & attacks))
        return 1;

    if((!list.count && !(king_position & attacks)) || (position_occurrences(t, hash_key) == 3))
        return 2;

    return 0;
}

long long evaluate_position(ChessBoard *board, const LookupTable *tbls, HashTable *t, Board_hash hash_key, int move)
{
    int factor = check_for_mate_or_path(board, tbls, t, hash_key);    
    
    if(factor == 1)
    {
        printf("found mate\n");
        return (board->turn == white) ? (CHECK_MATE_V * 10) : (-CHECK_MATE_V * 10);
    }
    
    if(factor == 2)
    {
        return 0;
    }

    return count_pieces(board);
}
