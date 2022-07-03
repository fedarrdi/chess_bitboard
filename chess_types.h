#ifndef CHESS_BIT_BOARDS_CHESS_TYPES_H
#define CHESS_BIT_BOARDS_CHESS_TYPES_H

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

typedef struct bit_chess_board
{
    Bitboard occupied[3];///by white by black by both
    /// index w_pawn, w_knight, w_bishop, w_queen, w_rook, w_king, b_pawn, b_knight, b_bishop, b_queen, b_rook, b_king
    Bitboard pieces[12];///every piece bitboard
} ChessBoard;

typedef struct bit_lookup_table
{
    Bitboard ClearRank[8], MaskRank[8], ClearFile[8], MaskFile[8];
}LookupTable;

#endif //CHESS_BIT_BOARDS_CHESS_TYPES_H
