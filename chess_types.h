#ifndef CHESS_BIT_BOARDS_CHESS_TYPES_H
#define CHESS_BIT_BOARDS_CHESS_TYPES_H

#define GET_BIT(bitboard, square) (bitboard & (1ULL << square))
#define SET_BIT(bitboard, square) (bitboard |= (1ULL << square))
#define POP_BIT(bitboard, square) ( GET_BIT(bitboard, square) ? (bitboard ^= (1ULL << square)) : 0 )

/*
            MOVE FROM                  000 0000 0000 0000 0000 0011 1111 6
            MOVE TO                    000 0000 0000 0000 1111 1100 0000 6
            MOVE PIECE                 000 0000 0000 1111 0000 0000 0000 4
            MOVE PROMOTION             000 0000 1111 0000 0000 0000 0000 4
            MOVE CAPTURE               000 1111 0000 0000 0000 0000 0000 4
            MOVE DOUBLE PUSH PAWN FLAG 001 0000 0000 0000 0000 0000 0000 1
            MOVE EN PASSANT FLAG       010 0000 0000 0000 0000 0000 0000 1
            MOVE CASTLING FLAG         100 0000 0000 0000 0000 0000 0000 1

                    THE MEMORY IS ROUNDED TO THAT OF AN INT
 */


#define ENCODE_MOVE(from, to, piece, promoted_piece, capture, double_pawn_push, enpassant, castling) \
(from) | \
((to) << 6) | \
((piece) << 12) | \
((promoted_piece) << 16) | \
((capture) << 20) | \
((double_pawn_push) << 24) | \
((enpassant) << 25) | \
((castling) << 26)

#define DECODE_MOVE_FROM(move) (move & 0x3f)
#define DECODE_MOVE_TO(move) ((move & 0xfc0) >> 6)
#define DECODE_MOVE_PIECE(move) ((move & 0xf000) >> 12)
#define DECODE_MOVE_PROMOTED_PIECE(move) ((move & 0xF0000) >> 16)
#define DECODE_MOVE_CAPTURE(move) ((move & 0xF00000) >> 20)
#define DECODE_MOVE_DOUBLE_PAWN_PUSH(move) (move & 0x1000000)
#define DECODE_MOVE_ENPASSANT(move) (move & 0x2000000)
#define DECODE_MOVE_CASTLING(move) (move & 0x4000000)

#define LIST_PUSH(list, move) list->moves[list->count++] = move
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
enum piece {w_pawn, w_knight, w_bishop, w_rook, w_queen, w_king, b_pawn, b_knight, b_bishop, b_rook, b_queen, b_king, empty};
enum file {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H};
enum rank {RANK_8, RANK_7, RANK_6, RANK_5, RANK_4, RANK_3, RANK_2, RANK_1};
enum castle {KC, QC, kc, qc};
enum bool {false, true};

typedef struct bit_chess_board
{
    Bitboard occupied[3];///by white by black by both
    /// index w_pawn, w_knight, w_bishop, w_queen, w_rook, w_king, b_pawn, b_knight, b_bishop, b_queen, b_rook, b_king
    Bitboard pieces[12];///every piece bitboard
    Bitboard en_passant[2]; /// 1 - for the places where white can take with en passant and 0 - for black
    char castles[4];/// white king side castle; wide queen side castle; black king side castle; black queen side castle
    enum color turn;///who moves in this position
} ChessBoard;

typedef struct bit_lookup_table
{
    Bitboard ClearRank[8], MaskRank[8], ClearFile[8], MaskFile[8];
} LookupTable;

struct move_list
{
    unsigned count;
    int moves[256];
};

#define MAX_LL 9223372036854775807


#endif //CHESS_BIT_BOARDS_CHESS_TYPES_H
