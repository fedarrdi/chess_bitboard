#include <stdio.h>
#include "chess_types.h"

void print_bitboard(U64 bitboard)
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

struct bit_chess_board fill_chess_board()
{
    struct bit_chess_board chess_board;
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


int main()
{
    struct bit_chess_board chess_board = fill_chess_board();

    for(int i = 0;i < 12;i++)
        print_bitboard(chess_board.pieces[i]);

    printf("\n\n\n");

    for(int i = 0;i < 3;i++)
        print_bitboard(chess_board.occupied[i]);

    return 0;
}
///https://pages.cs.wisc.edu/~psilord/blog/data/chess-pages/nonsliding.html
