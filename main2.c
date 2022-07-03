#include <stdio.h>

#define GET_BIT(bitboard, square) (bitboard & (1ULL << square))
#define SET_BIT(bitboard, square) (bitboard |= (1ULL << square))
#define POP_BIT(bitboard, square) ( GET_BIT(bitboard, square) ? (bitboard ^= (1ULL << square)) : 0 )

typedef unsigned long long Bitboard;

enum
{
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

enum color {black, white, both};
enum piece {w_pawn, w_knight, w_bishop, w_rook, w_queen, w_king, b_pawn, b_knight, b_bishop, b_rook, b_queen, b_king};
enum file {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H};
enum rank {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8};

struct bit_chess_board
{
    Bitboard occupied[3];///by white by black by both
    /// index w_pawn, w_knight, w_bishop, w_queen, w_rook, w_king, b_pawn, b_knight, b_bishop, b_queen, b_rook, b_king
    Bitboard  pieces[12];///every piece bitboard
};

struct bit_lookup_table
{
    Bitboard ClearRank[8];
    Bitboard MaskRank[8];
    Bitboard ClearFile[8];
    Bitboard MaskFile[8];
};

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

struct bit_lookup_table fill_lookup_table()
{
    struct bit_lookup_table tbls;
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


int main()
{
    struct bit_chess_board chess_board = fill_chess_board();

    for(int i = 0;i < 12;i++)
        print_bitboard(chess_board.pieces[i]);

    printf("\n\n\n");

    for(int i = 0;i < 3;i++)
        print_bitboard(chess_board.occupied[i]);


    struct bit_lookup_table tbls = fill_lookup_table();

    return 0;
}
