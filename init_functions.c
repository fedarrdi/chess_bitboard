#include "chess_types.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <limits.h>


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

LookupTable fill_lookup_table()
{
    LookupTable tbls;
    for(int i = 0;i < 8;i++)
    {
        tbls.ClearRank[i] = tbls.ClearFile[i] = ~(Bitboard)0;
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

ChessBoard parse_FEN(const char *FEN)
{
    ChessBoard board;

    for(int i = 0;i < 3;board.occupied[i++] = 0);
    for(int i = 0;i < 12;board.pieces[i++] = 0);

    int board_index = 0, rank = 0, file = 0, n = strlen(FEN), i;
    for(i = 0;i < n;i++)
    {
        if(FEN[i] == ' ') break;

        if(FEN[i] == '/') continue;

        if(FEN[i] >= '1' && FEN[i] <= '8')
        {
            file += FEN[i] - '0';
            continue;
        }

        if(FEN[i] >= 'A' && FEN[i] <= 'Z')
        {
            if(FEN[i] == 'P') board_index = w_pawn;
            if(FEN[i] == 'N') board_index = w_knight;
            if(FEN[i] == 'B') board_index = w_bishop;
            if(FEN[i] == 'R') board_index = w_rook;
            if(FEN[i] == 'Q') board_index = w_queen;
            if(FEN[i] == 'K') board_index = w_king;
        }

        if(FEN[i] >= 'a' && FEN[i] <= 'z')
        {
            if(FEN[i] == 'p') board_index = b_pawn;
            if(FEN[i] == 'n') board_index = b_knight;
            if(FEN[i] == 'b') board_index = b_bishop;
            if(FEN[i] == 'r') board_index = b_rook;
            if(FEN[i] == 'q') board_index = b_queen;
            if(FEN[i] == 'k') board_index = b_king;
        }
        if(file > 8)
        {
            rank ++;
            file -= 8;
        }

        int square = rank * 8 + file;
        SET_BIT(board.pieces[board_index], square);
        file++;
    }
    board.occupied[black] = board.pieces[b_rook]   | board.pieces[b_knight] |
                             board.pieces[b_bishop] | board.pieces[b_queen]  |
                             board.pieces[b_king]   | board.pieces[b_pawn];

    board.occupied[white] = board.pieces[w_rook]   | board.pieces[w_knight] |
                             board.pieces[w_bishop] | board.pieces[w_queen]  |
                             board.pieces[w_king]   | board.pieces[w_pawn];

    board.occupied[both] = board.occupied[white] | board.occupied[black];

    board.en_passant[0] = board.en_passant[1] = 0;

    if(FEN[++i] == 'w')
        board.turn = white;
    else if(FEN[i] == 'b')
        board.turn = black;

    for(int p = 0;p < 4;p++)
        board.castles[p] = 0;

    int j = 0;
    for(i+=2;j < 4;i++, j++)
    {
        if(FEN[i] == 'K') board.castles[KC] = 1;
        else if(FEN[i] == 'Q') board.castles[QC] = 1;
        else if(FEN[i] == 'k') board.castles[kc] = 1;
        else if(FEN[i] == 'q') board.castles[qc] = 1;
    }

    i++;

    int f = FEN[i++] - 'a', r = 8 - (FEN[i] - '0');

    board.en_passant[board.turn] = 1ULL << (r * 8 + f);
    board.en_passant[!board.turn] = 0;
    return board;
}

MoveList init_move_list()
{
    MoveList list;
    list.count = 0;
    for(int i = 0;i < 256;i++)
        list.moves[i] = 0;

    return list;
}