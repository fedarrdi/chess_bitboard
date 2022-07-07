#include "chess_types.h"
#include <stdio.h>

void print_chess_board(struct bit_chess_board *board)
{
    const char *piece_to_symbol = "PHBRQKphbrqk";

    printf("  X");
    for (int x = 0; x < 8; x++)
        printf("   %d", x);

    printf("\n");
    for(int y = 0;y < 8;y++)
    {
        printf("    |");
        for (int x = 0; x < 8; x++)
            printf("---+");

        printf("\n");
        printf("%d ->|", y);
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
    printf("  Y  ");
    printf("\n\n");
}



