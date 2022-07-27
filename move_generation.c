#include "chess_types.h"
#include <stdio.h>

Bitboard white_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard king_move(Bitboard king_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard knight_move(Bitboard knight_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard black_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard bishop_move(Bitboard bishop_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard rook_move(Bitboard rook_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard queen_move(Bitboard queen_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard white_pawn_attacks(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard black_pawn_attacks(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);

Bitboard (*attack_array[12])(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls) =
        {
                white_pawn_attacks, knight_move, bishop_move, rook_move, queen_move, king_move,
                black_pawn_attacks, knight_move, bishop_move, rook_move, queen_move, king_move
        };

int get_f1bit_index(Bitboard board)
{
    for(int i = 0;i < 64;i++)
        if(GET_BIT(board, i)) return i;
}

Bitboard calc_all_attacks(const ChessBoard *board, enum color side, const LookupTable *tbls)
{
    int start_index = side == white ? w_pawn : b_pawn;
    int end_index = side == white ? w_king : b_king;

    Bitboard attacks = 0;

    for(int i = start_index;i <= end_index; i++)
    {
        Bitboard copy_board = board->pieces[i];

        while(copy_board)
        {
            int bit_index = get_f1bit_index(copy_board);
            POP_BIT(copy_board, bit_index);
            attacks |= attack_array[i](1ULL << bit_index, board->occupied[side], board->occupied[!side], tbls);
        }
    }
    return attacks;
}

void generate_position_moves(const ChessBoard *board, enum color side, const LookupTable *tbls)
{
    int start_index = side == white ? w_pawn : b_pawn;
    int end_index = side == white ? w_king : b_king;

    for (int piece_index = start_index; piece_index < end_index; piece_index++)
    {
        Bitboard copy_position = board->pieces[piece_index];

        if(piece_index == b_pawn || piece_index == w_pawn)
        {
            while(copy_position)///en passant need to be added
            {
                int bit_index_from = get_f1bit_index(copy_position);
                POP_BIT(copy_position, bit_index_from);

                Bitboard pawn_moves = (side == white)
                        ? white_pawn_move(1ULL << bit_index_from, board->occupied[side], board->occupied[!side], tbls)
                        : black_pawn_move(1ULL << bit_index_from, board->occupied[side], board->occupied[!side], tbls);

                while(pawn_moves)
                {
                    int bit_index_to = get_f1bit_index(pawn_moves);
                    POP_BIT(pawn_moves, bit_index_to);

                    if((side == white && (1ULL << bit_index_to & tbls->MaskRank[RANK_8])))
                    {
                        printf("Pawn move: from %d -----> to %d promotion to white knight\n", bit_index_from, bit_index_to);
                        printf("Pawn move: from %d -----> to %d promotion to white bishop\n", bit_index_from, bit_index_to);
                        printf("Pawn move: from %d -----> to %d promotion to white rook\n", bit_index_from, bit_index_to);
                        printf("Pawn move: from %d -----> to %d promotion to white queen\n", bit_index_from, bit_index_to);

                    }

                    else if(side == black && ((1ULL << bit_index_to & tbls->MaskRank[RANK_1])))
                    {
                        printf("Pawn move: from %d -----> to %d promotion to black knight\n", bit_index_from, bit_index_to);
                        printf("Pawn move: from %d -----> to %d promotion to black bishop\n", bit_index_from, bit_index_to);
                        printf("Pawn move: from %d -----> to %d promotion to black rook\n", bit_index_from, bit_index_to);
                        printf("Pawn move: from %d -----> to %d promotion to black queen\n", bit_index_from, bit_index_to);
                    }

                    else
                    {
                        printf("Pawn move: from %d -----> to %d\n", bit_index_from, bit_index_to);
                    }
                }
            }
        }

        if(piece_index == w_bishop || piece_index == b_bishop || piece_index == w_knight || piece_index == b_knight ||
           piece_index == w_rook || piece_index == b_rook || piece_index == w_queen || piece_index == b_queen)
        {
            while(copy_position)///need to check if the piece is moved does it result in check
            {
                int bit_index_from = get_f1bit_index(copy_position);
                POP_BIT(copy_position, bit_index_from);
                Bitboard piece_moves = attack_array[piece_index](1ULL << bit_index_from, board->occupied[side], board->occupied[!side], tbls);
                while(piece_moves)
                {
                    int bit_index_to = get_f1bit_index(piece_moves);
                    POP_BIT(piece_moves, bit_index_to);

                    if(piece_index == w_bishop || piece_index == b_bishop) printf("Bishop ");
                    if(piece_index == w_knight || piece_index == b_knight) printf("Knight ");
                    if(piece_index == w_rook || piece_index == b_rook) printf("Rook ");
                    if(piece_index == w_queen || piece_index == b_queen) printf("Queen ");

                    printf("move: from %d -----> to %d\n", bit_index_from, bit_index_to);
                }
            }
        }

        if(piece_index == w_king || piece_index == b_king)///need to add castle
        {
            Bitboard enemy_attacks = calc_all_attacks(board, !side, tbls);
            Bitboard king_incomplete_moves = king_move(copy_position, board->occupied[side], board->occupied[!side], tbls);
            Bitboard king_moves = king_incomplete_moves & ~enemy_attacks;

            int bit_index_from = get_f1bit_index(copy_position);
            while(king_moves)
            {
                int bit_index_to = get_f1bit_index(king_moves);
                POP_BIT(king_moves, bit_index_to);
                printf("King move: from %d -----> to %d\n", bit_index_from, bit_index_to);
            }

            if(side == white && board->castles[KC])
            {

            }

            if(side == white && board->castles[QC])
            {

            }

            if(side == black && board->castles[kc])
            {

            }

            if(side == black && board->castles[qc])
            {

            }

        }

    }

}