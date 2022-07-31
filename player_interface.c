#include "chess_types.h"
#include <stdio.h>

void print_chess_board(ChessBoard *board)
{
    const char *piece_to_symbol = "PHBRQKphbrqk";

    printf("\n");
    for(int y = 0;y < 8;y++)
    {
        printf("    |");
        for (int x = 0; x < 8; x++)
            printf("---+");

        printf("\n");
        printf("%d ->|", 8 - y);
        for(int x = 0;x < 8;x++)
        {
            int square = y * 8 + x;
            char curr_piece = ' ';

            if((board->occupied[both] & (1ULL << square)))
                for(int piece_index = 0;piece_index < 12; piece_index++)
                    if((board->pieces[piece_index] & (1ULL << square))) {
                        curr_piece = piece_to_symbol[piece_index];
                        break;
                    }
            printf(" %c |", curr_piece);
        }
        if (y == 8 - 1)
        {
            printf("\n"); printf("    |");
            for (int x = 0; x < 8; x++)
                printf("---+");
        }
        printf("\n");
    }
    printf("      A   B   C   D   E   F   G   H");
    printf("\n\n");
}


void print_move(int move)
{

    const char *square_string[] = {"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
                                   "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
                                   "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
                                   "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
                                   "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
                                   "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
                                   "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
                                   "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"};

    const char *piece_to_symbol = "PHBRQKphbrqk0";

    printf("MOVE from: %s\n", square_string[DECODE_MOVE_FROM(move)]);
    printf("MOVE to: %s\n", square_string[DECODE_MOVE_TO(move)]);
    printf("MOVE piece: %c\n", piece_to_symbol[DECODE_MOVE_PIECE(move)]);
    DECODE_MOVE_PROMOTED_PIECE(move) ?  printf("MOVE promoted piece: %c\n", piece_to_symbol[DECODE_MOVE_PROMOTED_PIECE(move)]) :  printf("MOVE promoted piece: NONE");
    printf("MOVE capture piece: %c\n", piece_to_symbol[DECODE_MOVE_CAPTURE(move)]);
    printf("MOVE is double pawn push: %d\n", DECODE_MOVE_DOUBLE_PAWN_PUSH(move) ? 1 : 0);
    printf("MOVE is en passant: %d\n", DECODE_MOVE_ENPASSANT(move) ? 1 : 0);
    printf("MOVE is castle: %d\n", DECODE_MOVE_CASTLING(move) ? 1 : 0);
}
