#include "chess_types.h"
#include "move_generation.h"
#include <stdlib.h>

Bitboard get_random_64bit_number()
{
    // Assuming RAND_MAX is 2^31.
    Bitboard r = rand();
    r = r << 30 | rand();
    r = r << 30 | rand();
    return r;
}

struct random_keys init_random_keys()
{
    struct random_keys random_keys;

    for(enum piece p = w_pawn; p <= b_king; p++)
    {
        for(int square = 0; square < 64; square ++)
        {
            random_keys.piece[p][square] = get_random_64bit_number();
        }
    }

    for(int i = 0;i < 16;i++)
        random_keys.castle[i] = get_random_64bit_number();

    for(int i = 0;i < 64;i++)
        random_keys.enpassant[i] = get_random_64bit_number();

    random_keys.side = get_random_64bit_number();

    return random_keys;
}

Board_hash get_bord_hash(const ChessBoard *board, const Keys *keys)
{
    Board_hash board_hash = 0;

    for(enum piece p = w_pawn; p <= b_king; p++)
    {
        Bitboard curr_board = board->pieces[p];

        while(curr_board)
        {
            int square = get_f1bit_index(curr_board);
            board_hash ^= keys->piece[p][square];
            POP_BIT(curr_board, square);
        }
    }

    int castle_index = 0;
    for(int i = 0;i < 4;i++)
    {
        if (board->castles[i])
        {
            if(i == 0)
                castle_index |= 1;
            else
                castle_index |= 2 << i;
        }
    }
    board_hash ^= keys->castle[castle_index];


    if(board->en_passant[board->turn])
    {
        int enpassant_square = get_f1bit_index(board->en_passant[board->turn]);
        board_hash ^= keys->enpassant[enpassant_square];
    }


    if(board->turn)
        board_hash ^= keys->side;

    return board_hash;
}