#include "chess_types.h"
#include "player_types.h"
#include <stdio.h>

Bitboard white_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls);
Bitboard king_move(Bitboard king_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls);
Bitboard knight_move(Bitboard knight_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls);
Bitboard black_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls);
Bitboard bishop_move(Bitboard bishop_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls);
Bitboard rook_move(Bitboard rook_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls);
Bitboard queen_move(Bitboard queen_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls);

Bitboard (*piece_move_f[12])(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, LookupTable *tbls) =
        {
           white_pawn_move,knight_move,bishop_move,rook_move,queen_move,king_move,
           black_pawn_move,knight_move,bishop_move,rook_move,queen_move,king_move
        };

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

void player_play_move(ChessBoard *board, enum color color, LookupTable *tbls)
{
    Position from;

    back:;
    printf("Enter cords of piece you want to move.\n");
    char file;
    scanf("%c", &file);
    scanf("%d", &from.y);

    from.y = 8 - from.y;
    from.x = (int)(file - 'a');

    if(from.x < 0 || from.x > 7 || from.y < 0 || from.y > 7)
    {
        printf("Invalid cords!!!\n");
        goto back;
    }

    int from_square = from.y * 8 + from.x;

    if(!GET_BIT(board->occupied[both], from_square))
    {
        printf("there isn't a piece on this position!!!\n");
        goto back;
    }

    if(!GET_BIT(board->occupied[color], from_square))
    {
        printf("This piece is not yours!!!\n");
        goto back;
    }

    Bitboard piece_moves = 0, piece_pos = 0;
    SET_BIT(piece_pos, from_square);

    int piece_index = 0;
    for(;piece_index < 12;piece_index++)
        if(GET_BIT(board->pieces[piece_index], from_square))
        {
            piece_moves = piece_move_f[piece_index](piece_pos, board->occupied[color], board->occupied[!color], tbls);
            break;
        }

    if(!piece_moves)
    {
        printf("This piece has no moves!!!\n");
        goto back;
    }

    Position to;

    back1:;
    printf("Enter where you want to move the piece.\n");
    scanf("%c", &file);
    scanf("%d", &to.y);
    to.y = 8 - to.y;
    to.x = (int)(file - 'a');

    if(to.x < 0 || to.x > 7 || to.y < 0 || to.y > 7)
    {
        printf("Invalid cords!!!\n");
        goto back1;
    }

    int to_square = to.y * 8 + to.x;
    if(!GET_BIT(piece_moves, to_square))
    {
        printf("This move is not valid!!!\n");
        goto back1;
    }

    ///make the move on the board
    POP_BIT(board->pieces[piece_index], from_square);
    SET_BIT(board->pieces[piece_index], to_square);
    POP_BIT(board->occupied[color], from_square);
    SET_BIT(board->occupied[color], to_square);
    POP_BIT(board->occupied[both], from_square);
    SET_BIT(board->occupied[both], to_square);
}