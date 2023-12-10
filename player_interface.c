#include <stdio.h>
#include "chess_types.h"
#include "move_generation.h"
#include "position_hash_table.h"
#include "zobrist_hashing.h"

void print_piece(int piece_type)
{
    switch (piece_type)
    {
        case 0: printf(" \u265F |"); break;
        case 1: printf(" \u265E |"); break;
        case 2: printf(" \u265D |"); break;
        case 3: printf(" \u265C |"); break;
        case 4:printf(" \u265B |"); break;
        case 5:printf(" \u265A |"); break;
        case 6: printf(" \u2659 |"); break;
        case 7: printf(" \u2658 |"); break;
        case 8: printf(" \u2657 |"); break;
        case 9: printf(" \u2656 |"); break;
        case 10: printf(" \u2655 |"); break;
        case 11: printf(" \u2654 |"); break;
        default: printf("   |"); break;
    }
}

void print_chess_board(ChessBoard *board)
{
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
            int piece = empty; 
            if((board->occupied[both] & (1ULL << square)))
                for(int piece_index = 0;piece_index < 12; piece_index++)
                    if((board->pieces[piece_index] & (1ULL << square)))
                    {
                        piece = piece_index;
                        break;
                    }
            print_piece(piece);
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
    printf("MOVE promotion: %c\n", piece_to_symbol[DECODE_MOVE_PROMOTED_PIECE(move)]);
    printf("MOVE capture piece: %c\n", piece_to_symbol[DECODE_MOVE_CAPTURE(move)]);
    printf("MOVE is double pawn push: %d\n", DECODE_MOVE_DOUBLE_PAWN_PUSH(move) ? 1 : 0);
    printf("MOVE is en passant: %d\n", DECODE_MOVE_ENPASSANT(move) ? 1 : 0);
    printf("MOVE is castle: %d\n", DECODE_MOVE_CASTLING(move) ? 1 : 0);

    printf("\n MOVE VALUE: %d\n\n", move);

}
/*
void player_make_move(ChessBoard *board, const LookupTable *tbls, const Keys *keys, HashTable *t)
{
    enum color side = board->turn;

    int rank;
    char file;

    back:;

    printf("Please enter file and rank.\n");
    scanf(" %c %d", &file ,&rank);

    while(file < 'A' || file > 'H')
    {
        printf("File incorrect!\n");
        printf("Please enter file.\n");
        scanf("%c", &file);
    }
    int from_square = (8 - rank) * 8 + file - 'A';


    while(rank < 0 || rank > 8)
    {
        printf("Rank incorrect!\n");
        printf("Please enter Rank.\n");
        scanf("%d", &rank);
    }
    int to_square = (8 - rank1) * 8 + file1 - 'A';


    enum piece curr_piece = 0;
    for(enum piece i = w_pawn;i <= b_king; i++)
    {
        if(board->pieces[i] & 1ULL << from_square)
        {
            piece = i;
            break;
        }
    }
    
    if(piece == w_pawn)
    {
            
    }

    if(piece == b_pawn)
    {


    }

}*/

void player_make_move(ChessBoard *board, const LookupTable *tbls, const Keys *keys, HashTable *t)
{
    enum color side = board->turn;

    int rank;
    char file;

    back:;

    printf("Please enter file and rank.\n");
    scanf(" %c %d", &file ,&rank);

    while(file < 'A' || file > 'H')
    {
        printf("File incorrect!\n");
        printf("Please enter file.\n");
        scanf("%c", &file);
    }

    while(rank < 0 || rank > 8)
    {
        printf("Rank incorrect!\n");
        printf("Please enter Rank.\n");
        scanf("%d", &rank);
    }

    int from_square = (8 - rank) * 8 + file - 'A';

    int piece = 0;

    for(int i = w_pawn;i <= b_king; i++)
        if(board->pieces[i] & 1ULL << from_square)
        {
            piece = i;
            break;
        }

    if(!get_piece_move(piece, 1ULL << from_square, board->occupied[side], board->occupied[!side], tbls))
    {
        printf("This piece has no moves.\n");
        goto back;
    }

    if(!GET_BIT(board->occupied[side], from_square))
    {
        printf("This square doesn't have a piece of your color!\n");
        goto back;
    }

    back1:;
    int rank1;
    char file1;
    printf("Please enter file and rank.\n");
    scanf(" %c %d", &file1 ,&rank1);

    while(file1 < 'A' || file1 > 'H')
    {
        printf("File incorrect!\n");
        printf("Please enter file.\n");
        scanf("%c", &file1);
    }

    while(rank1 < 0 || rank1 > 8)
    {
        printf("Rank incorrect!\n");
        printf("Please enter Rank.\n");
        scanf("%d", &rank1);
    }

    /// need to fix castle for player move and enpassant
    int to_square = (8 - rank1) * 8 + file1 - 'A';
    
    Bitboard king_board = (board->turn == white) ? board->pieces[w_king] : board->pieces[b_king];
       

    if(GET_BIT(from_square, king_board))
    {
    }

    if(board->turn == white)
    {
        if(GET_BIT(from_square, king_board))
        {

        }
        
    }

    if(board->turn == black)
    {


    }

    if(!(get_piece_move(piece, 1ULL << from_square, board->occupied[side], board->occupied[!side], tbls) & 1ULL << to_square))
    {
        printf("This move is invalid.\n");
        goto back1;
    }

    if(GET_BIT(board->occupied[side], to_square))
    {
        printf("This square has a piece of yours , you can't move there!\n");
        goto back1;
    }

    POP_BIT(board->occupied[both], from_square);
    POP_BIT(board->occupied[side], from_square);
    POP_BIT(board->pieces[piece], from_square);


    if(GET_BIT(board->occupied[!side], to_square))  /// move is capture
    {
        POP_BIT(board->occupied[!side], to_square);

        for(int i = w_pawn; i <= b_king; i++)
            POP_BIT(board->pieces[i], to_square);
    }

    SET_BIT(board->occupied[both], to_square);
    SET_BIT(board->occupied[side], to_square);
    SET_BIT(board->pieces[piece], to_square);

    Bitboard enemy_attacks = generate_all_attacks(board, tbls);

    int king_index = side == white ? w_king : b_king;
    if(enemy_attacks & board->pieces[king_index])
    {
        printf("This move exposes king to check.\n");
        goto back;
    }

    Board_hash hash = get_bord_hash(board, keys);
    insert_item(t, hash);
}

void print_move_list(const MoveList *list)
{
    printf("\n\n\n**************** Position moves ****************\n\n\n");
    for(int i = 0;i < list->count;i++)
        if(list->moves[i])
            print_move(list->moves[i]);

    printf("\n\n\n************************************************\n\n\n");
}
