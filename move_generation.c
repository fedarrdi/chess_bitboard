#include "chess_types.h"

Bitboard white_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard king_move(Bitboard king_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard knight_move(Bitboard knight_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard black_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard bishop_move(Bitboard bishop_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard rook_move(Bitboard rook_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard queen_move(Bitboard queen_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);

int get_f1bit_index(Bitboard board)
{
    for(int i = 0;i < 64;i++)
        if(GET_BIT(board, i)) return i;
}

void generate_position_moves(const ChessBoard *board, enum color side, const LookupTable *tbls)
{
    int start_index = side == white ? w_pawn : b_pawn;
    int end_index = side == white ? w_king : b_king;
    Bitboard curr_piece_moves = 0;

    for (int piece_index = start_index; piece_index < end_index; piece_index++)
    {
        Bitboard copy_position = board->pieces[piece_index];


        if(piece_index == w_pawn)
        {

            while(copy_position)
            {
                int bit_index_from = get_f1bit_index(copy_position);
                POP_BIT(copy_position, bit_index_from);
                Bitboard white_pawn_moves = white_pawn_move(1ULL << bit_index_from, board->occupied[side], board->occupied[!side], tbls);

                while(white_pawn_moves)
                {
                    int bit_index_to = get_f1bit_index(white_pawn_moves);
                    POP_BIT(white_pawn_moves, bit_index_to);
                }
            }

        }

        if(piece_index == b_pawn)
        {

        }

        if(piece_index == w_bishop || piece_index == b_bishop)
        {

        }

        if(piece_index == w_knight || piece_index == b_knight)
        {

        }

        if(piece_index == w_rook || piece_index == b_rook)
        {

        }

        if(piece_index == w_queen || piece_index == b_queen)
        {

        }

        if(piece_index == w_king || piece_index == b_king)
        {

        }
    }
}