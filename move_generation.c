#include "chess_types.h"
#include <stdio.h>
void print_bitboard(Bitboard bitboard);
Bitboard white_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard king_move(Bitboard king_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard knight_move(Bitboard knight_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard black_pawn_move(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard bishop_move(Bitboard bishop_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard rook_move(Bitboard rook_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard queen_move(Bitboard queen_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard white_pawn_attacks(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);
Bitboard black_pawn_attacks(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls);

Bitboard (*attack_array[12])(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls) =
        {
                white_pawn_attacks, knight_move, bishop_move, rook_move, queen_move, king_move,
                black_pawn_attacks, knight_move, bishop_move, rook_move, queen_move, king_move
        };

Bitboard (*move_array[12])(Bitboard pawn_pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls) =
        {
                white_pawn_move, knight_move, bishop_move, rook_move, queen_move, king_move,
                black_pawn_move, knight_move, bishop_move, rook_move, queen_move, king_move
        };

int get_f1bit_index(Bitboard board)
{
    for(int i = 0;i < 64;i++)
        if(GET_BIT(board, i)) return i;
    return -1;
}

Bitboard get_piece_move(enum piece piece, Bitboard pos, Bitboard own_side, Bitboard enemy_side, const LookupTable *tbls)
{
    return move_array[piece](pos, own_side, enemy_side, tbls);
}

Bitboard generate_all_attacks(const ChessBoard *board, enum color side, const LookupTable *tbls)
{
    int start_index = side == white ? w_pawn : b_pawn;
    int end_index = side == white ? w_king : b_king;

    Bitboard attacks = 0;

    for(int i = start_index;i <= end_index; i++)
    {
        Bitboard copy_board = board->pieces[i];

        while(copy_board)
        {
            int bit_index = get_f1bit_index(copy_board);
            POP_BIT(copy_board, bit_index);
            attacks |= attack_array[i](1ULL << bit_index, board->occupied[side], board->occupied[!side], tbls);
        }
    }
    return attacks;
}
                        /// need to push moves in the move list
void generate_position_moves(struct move_list *empty_list, ChessBoard *board, enum color side, const LookupTable *tbls)
{
    int start_index = side == white ? w_pawn : b_pawn;
    int end_index = side == white ? w_king : b_king;
    Bitboard enemy_attacks = generate_all_attacks(board, !side, tbls);

    for (int piece_index = start_index; piece_index <= end_index; piece_index++)
    {
        Bitboard copy_position = board->pieces[piece_index];

        if(piece_index == b_pawn || piece_index == w_pawn)
        {
            while(copy_position)
            {
                int bit_index_from = get_f1bit_index(copy_position);
                POP_BIT(copy_position, bit_index_from);

                Bitboard pawn_moves = (side == white)
                        ? white_pawn_move(1ULL << bit_index_from, board->occupied[side], board->occupied[!side], tbls)
                        : black_pawn_move(1ULL << bit_index_from, board->occupied[side], board->occupied[!side], tbls);


                POP_BIT(board->pieces[piece_index], bit_index_from);
                POP_BIT(board->pieces[piece_index], bit_index_from);

                while(pawn_moves)
                {
                    int bit_index_to = get_f1bit_index(pawn_moves);
                    POP_BIT(pawn_moves, bit_index_to);


                    SET_BIT(board->pieces[piece_index], bit_index_to);
                    Bitboard secret_king_attacks = generate_all_attacks(board, !side, tbls);
                    if(bit_index_from == 51)
                    {
                        print_bitboard(secret_king_attacks);
                        print_bitboard(board->pieces[piece_index]);
                    }

                    if(!(secret_king_attacks & board->pieces[end_index]))
                    {
                        if ((side == white && (1ULL << bit_index_to & tbls->MaskRank[RANK_8])))
                        {

                            printf("Pawn move: from %d -----> to %d promotion to white knight\n", bit_index_from, bit_index_to);
                            printf("Pawn move: from %d -----> to %d promotion to white bishop\n", bit_index_from, bit_index_to);
                            printf("Pawn move: from %d -----> to %d promotion to white rook\n", bit_index_from, bit_index_to);
                            printf("Pawn move: from %d -----> to %d promotion to white queen\n", bit_index_from, bit_index_to);

                        }
                        else if (side == black && ((1ULL << bit_index_to & tbls->MaskRank[RANK_1])))
                        {
                            printf("Pawn move: from %d -----> to %d promotion to black knight\n", bit_index_from, bit_index_to);
                            printf("Pawn move: from %d -----> to %d promotion to black bishop\n", bit_index_from, bit_index_to);
                            printf("Pawn move: from %d -----> to %d promotion to black rook\n", bit_index_from, bit_index_to);
                            printf("Pawn move: from %d -----> to %d promotion to black queen\n", bit_index_from, bit_index_to);
                        }
                        else
                            printf("Pawn move: from %d -----> to %d\n", bit_index_from, bit_index_to);

                    }
                    POP_BIT(board->pieces[piece_index], bit_index_to);
                }
                SET_BIT(board->pieces[piece_index], bit_index_from);
            }
        }

        if(piece_index == w_bishop || piece_index == b_bishop || piece_index == w_knight || piece_index == b_knight ||
           piece_index == w_rook || piece_index == b_rook || piece_index == w_queen || piece_index == b_queen)
        {
            while(copy_position)
            {
                int bit_index_from = get_f1bit_index(copy_position);
                POP_BIT(copy_position, bit_index_from);
                Bitboard piece_moves = attack_array[piece_index](1ULL << bit_index_from, board->occupied[side], board->occupied[!side], tbls);
                while(piece_moves)
                {
                    int bit_index_to = get_f1bit_index(piece_moves);
                    POP_BIT(piece_moves, bit_index_to);

                    if(piece_index == w_bishop || piece_index == b_bishop) printf("Bishop ");
                    if(piece_index == w_knight || piece_index == b_knight) printf("Knight ");
                    if(piece_index == w_rook || piece_index == b_rook) printf("Rook ");
                    if(piece_index == w_queen || piece_index == b_queen) printf("Queen ");

                    printf("move: from %d -----> to %d\n", bit_index_from, bit_index_to);
                }
            }
        }

        if(piece_index == w_king || piece_index == b_king)
        {
            Bitboard king_incomplete_moves = king_move(copy_position, board->occupied[side], board->occupied[!side], tbls);
            Bitboard king_moves = king_incomplete_moves & ~enemy_attacks;

            int bit_index_from = get_f1bit_index(copy_position);
            while(king_moves)
            {
                int bit_index_to = get_f1bit_index(king_moves);
                POP_BIT(king_moves, bit_index_to);
                printf("King move: from %d -----> to %d\n", bit_index_from, bit_index_to);
            }

            if(side == white && board->castles[KC])
                if(!GET_BIT(board->occupied[side], f1) && !GET_BIT(board->occupied[side], g1) && !((1ULL << f1) & enemy_attacks) &&  !((1ULL << g1) & enemy_attacks))
                    printf("King side castle\n");

            if(side == white && board->castles[QC])
                if(!GET_BIT(board->occupied[side], b1) && !GET_BIT(board->occupied[side], c1) && !GET_BIT(board->occupied[side], d1)
                                                       && !((1ULL << c1) & enemy_attacks)        && !((1ULL << d1) & enemy_attacks))
                    printf("Queen side castle\n");

            if(side == black && board->castles[kc])
                if(!GET_BIT(board->occupied[side], f8) && !GET_BIT(board->occupied[side], g8) && !((1ULL << f8) & enemy_attacks) &&  !((1ULL << g8) & enemy_attacks))
                    printf("King side castle\n");

            if(side == black && board->castles[qc])
                if(!GET_BIT(board->occupied[side], b8) && !GET_BIT(board->occupied[side], c8) && !GET_BIT(board->occupied[side], d8)
                   && !((1ULL << c8) & enemy_attacks)        && !((1ULL << d8) & enemy_attacks))
                    printf("Queen side castle\n");
        }
    }
}

void play_move(int move, ChessBoard *board, const LookupTable *tbls, enum color side)
{
    int from = DECODE_MOVE_FROM(move),
        to = DECODE_MOVE_TO(move),
        piece = DECODE_MOVE_PIECE(move),
        prom_piece = DECODE_MOVE_PIECE(move),
        capture_piece = DECODE_MOVE_CAPTURE(move),
        double_pawn_push = DECODE_MOVE_DOUBLE_PAWN_PUSH(move),
        enpassant = DECODE_MOVE_ENPASSANT(move),
        castling = DECODE_MOVE_CASTLING(move);

    POP_BIT(board->occupied[both], from);
    POP_BIT(board->occupied[side], from);
    POP_BIT(board->pieces[piece], from);

    if(capture_piece)
    {
        POP_BIT(board->occupied[!side], to);
        for(int i = w_pawn; i <= b_king; i++)
            POP_BIT(board->pieces[i], to);
    }

    SET_BIT(board->occupied[both], to);
    SET_BIT(board->occupied[side], to);
    SET_BIT(board->pieces[piece], to);
}

void undo_move(int move, ChessBoard *board, const LookupTable *tbls, enum color side)
{
    int from = DECODE_MOVE_FROM(move),
        to = DECODE_MOVE_TO(move),
        piece = DECODE_MOVE_PIECE(move),
        prom_piece = DECODE_MOVE_PIECE(move),
        capture_piece = DECODE_MOVE_CAPTURE(move),
        double_pawn_push = DECODE_MOVE_DOUBLE_PAWN_PUSH(move),
        enpassant = DECODE_MOVE_ENPASSANT(move),
        castling = DECODE_MOVE_CASTLING(move);

    POP_BIT(board->occupied[both], to);
    POP_BIT(board->occupied[side], to);
    POP_BIT(board->pieces[piece], to);

    SET_BIT(board->occupied[both], from);
    SET_BIT(board->occupied[side], from);
    SET_BIT(board->pieces[piece], from);

    SET_BIT(board->occupied[both], to);
    SET_BIT(board->occupied[!side], to);
    SET_BIT(board->pieces[capture_piece], to);
}

void sieve_moves(struct move_list *list, ChessBoard *board, const LookupTable *tbls, enum color side)
{
    for(int i = 0;i < list->count;i++)
    {
        play_move(list->moves[i], board, tbls, side);
        Bitboard enemy_attacks = generate_all_attacks(board, !side, tbls);
        Bitboard king_position = side == white ? board->pieces[w_king] : board->pieces[b_king];

        if(king_position & enemy_attacks)
            list->moves[i] = 0;

        undo_move(list->moves[i], board, tbls, side);
    }
}

void print_move(int move);

void print_move_list(const struct move_list *list)
{
    for(int i = 0;i < list->count;i++)
        if(list->moves[i])
            print_move(list->moves[i]);
}