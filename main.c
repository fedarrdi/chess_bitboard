#include <stdio.h>
#include "chess_types.h"

void print_bitboard(Bitboard bitboard)
{
    for(int rank = 0; rank < 8; rank++)
    {
        printf(" %d  ", 8 - rank);
        for(int file = 0; file < 8; file++)
        {
            int square = rank * 8 + file;

            printf(" %d ", GET_BIT(bitboard, square) ? 1 : 0);
        }
        printf("\n");
    }

    printf("\n     A  B  C  D  E  F  G  H\n\n");

    printf("Bitboard : %llu\n\n", bitboard);
}

ChessBoard fill_chess_board()
{
    ChessBoard chess_board;
    for(int i = 0;i < 3;chess_board.occupied[i++] = 0);
    for(int i = 0;i < 12;chess_board.pieces[i++] = 0);

    for(int i = 0;i < 8;i++)
    {
        int b_pawn_square = 8 + i, w_pawn_square = 6 * 8 + i;
        SET_BIT(chess_board.pieces[b_pawn], b_pawn_square);
        SET_BIT(chess_board.pieces[w_pawn], w_pawn_square);
    }

    SET_BIT(chess_board.pieces[b_rook], a8);
    SET_BIT(chess_board.pieces[b_rook], h8);
    SET_BIT(chess_board.pieces[w_rook], a1);
    SET_BIT(chess_board.pieces[w_rook], h1);

    SET_BIT(chess_board.pieces[b_knight], b8);
    SET_BIT(chess_board.pieces[b_knight], g8);
    SET_BIT(chess_board.pieces[w_knight], b1);
    SET_BIT(chess_board.pieces[w_knight], g1);

    SET_BIT(chess_board.pieces[b_bishop], c8);
    SET_BIT(chess_board.pieces[b_bishop], f8);
    SET_BIT(chess_board.pieces[w_bishop], c1);
    SET_BIT(chess_board.pieces[w_bishop], f1);

    SET_BIT(chess_board.pieces[b_queen], d8);
    SET_BIT(chess_board.pieces[w_queen], d1);

    SET_BIT(chess_board.pieces[b_king], e8);
    SET_BIT(chess_board.pieces[w_king], e1);

    chess_board.occupied[black] = chess_board.pieces[b_rook]   | chess_board.pieces[b_knight] |
                                  chess_board.pieces[b_bishop] | chess_board.pieces[b_queen]  |
                                  chess_board.pieces[b_king]   | chess_board.pieces[b_pawn];

    chess_board.occupied[white] = chess_board.pieces[w_rook]   | chess_board.pieces[w_knight] |
                                  chess_board.pieces[w_bishop] | chess_board.pieces[w_queen]  |
                                  chess_board.pieces[w_king]   | chess_board.pieces[w_pawn];

    chess_board.occupied[both] = chess_board.occupied[white] | chess_board.occupied[black];

    return chess_board;
}

LookupTable fill_lookup_table()
{
    LookupTable tbls;
    for(int i = 0;i < 8;i++)
    {
        tbls.ClearRank[i] = tbls.ClearFile[i] = (Bitboard)~0;
        tbls.MaskRank[i] = tbls.MaskFile[i] = 0;
    }

    Bitboard tmp1 = 1, tmp2;
    for(int i = 0;i < 8;i++)
    {
        tmp2 = 1 << i;
        for(int j = 0;j < 8;j++)
        {
            tbls.ClearRank[i] ^= tmp1;
            tmp1 <<= 1;
            tbls.ClearFile[i] ^= tmp2;
            tmp2 <<= 8;
        }
    }

    for(int i = 0;i < 8;i++)
    {
        tbls.MaskRank[i] = ~tbls.ClearRank[i];
        tbls.MaskFile[i] = ~tbls.ClearFile[i];
    }

    return tbls;
}

Bitboard knight_move(Bitboard knight_pos, Bitboard own_side, LookupTable *tbls);


int main()
{
    Bitboard knight_board = 0;
    SET_BIT(knight_board, a4);

    Bitboard own_side = 0;
    LookupTable tbls = fill_lookup_table();

    Bitboard out = knight_move(knight_board, own_side, &tbls);
    print_bitboard(out);
    return 0;
}
