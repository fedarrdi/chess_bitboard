#include "chess_types.h"

/// need to change board turn after every move
void play_move(int move, ChessBoard *board)
{
    board->en_passant[board->turn] = 0;

    int from = DECODE_MOVE_FROM(move),
            to = DECODE_MOVE_TO(move),
            piece = DECODE_MOVE_PIECE(move),
            prom_piece = DECODE_MOVE_PROMOTED_PIECE(move),
            capture_piece = DECODE_MOVE_CAPTURE(move),
            double_pawn_push_flag = DECODE_MOVE_DOUBLE_PAWN_PUSH(move),
            enpassant_flag = DECODE_MOVE_ENPASSANT(move),
            castling_flag = DECODE_MOVE_CASTLING(move);

    if (castling_flag)
    {
        if (board->turn == white)
        {
            if (from < to)
            {
                POP_BIT(board->pieces[w_king], e1);
                POP_BIT(board->occupied[white], e1);
                POP_BIT(board->occupied[both], e1);

                POP_BIT(board->pieces[w_rook], h1);
                POP_BIT(board->occupied[white], h1);
                POP_BIT(board->occupied[both], h1);

                SET_BIT(board->pieces[w_king], g1);
                SET_BIT(board->occupied[white], g1);
                SET_BIT(board->occupied[both], g1);

                SET_BIT(board->pieces[w_rook], f1);
                SET_BIT(board->occupied[white], f1);
                SET_BIT(board->occupied[both], f1);
            }
            else if (from > to)   /// queen side castle
            {
                POP_BIT(board->pieces[w_king], e1);
                POP_BIT(board->occupied[white], e1);
                POP_BIT(board->occupied[both], e1);

                POP_BIT(board->pieces[w_rook], a1);
                POP_BIT(board->occupied[white], a1);
                POP_BIT(board->occupied[both], a1);

                SET_BIT(board->pieces[w_king], c1);
                SET_BIT(board->occupied[white], c1);
                SET_BIT(board->occupied[both], c1);

                SET_BIT(board->pieces[w_rook], d1);
                SET_BIT(board->occupied[white], d1);
                SET_BIT(board->occupied[both], d1);
            }
        }
        else if (board->turn == black)
        {
            if (from < to) /// king side castle
            {
                POP_BIT(board->pieces[b_king], e8);
                POP_BIT(board->occupied[black], e8);
                POP_BIT(board->occupied[both], e8);

                POP_BIT(board->pieces[b_rook], h8);
                POP_BIT(board->occupied[black], h8);
                POP_BIT(board->occupied[both], h8);

                SET_BIT(board->pieces[b_king], g8);
                SET_BIT(board->occupied[black], g8);
                SET_BIT(board->occupied[both], g8);

                SET_BIT(board->pieces[b_rook], f8);
                SET_BIT(board->occupied[black], f8);
                SET_BIT(board->occupied[both], f8);
            }
            else if (from > to)  /// queen side castle
            {
                POP_BIT(board->pieces[b_king], e8);
                POP_BIT(board->occupied[black], e8);
                POP_BIT(board->occupied[both], e8);

                POP_BIT(board->pieces[b_rook], a8);
                POP_BIT(board->occupied[black], a8);
                POP_BIT(board->occupied[both], a8);

                SET_BIT(board->pieces[b_king], c8);
                SET_BIT(board->occupied[black], c8);
                SET_BIT(board->occupied[both], c8);

                SET_BIT(board->pieces[b_rook], d8);
                SET_BIT(board->occupied[black], d8);
                SET_BIT(board->occupied[both], d8);
            }
        }
    }
    if(double_pawn_push_flag)
    {
        board->en_passant[!board->turn] |= (board->turn == white) ? (1ULL << from) << 8 :  (1ULL << from) >> 8;
    }
    if(enpassant_flag)
    {
        POP_BIT(board->occupied[both], from);
        POP_BIT(board->occupied[board->turn], from);
        POP_BIT(board->pieces[piece], from);

        int capture = (board->turn == white) ? to + 8 : to - 8;
        enum piece capture_pawn = (board->turn == white) ? b_pawn : w_pawn;

        POP_BIT(board->occupied[both], capture);
        POP_BIT(board->occupied[!board->turn], capture);
        POP_BIT(board->pieces[capture_pawn], from);

        SET_BIT(board->occupied[both], to);
        SET_BIT(board->occupied[board->turn], to);
        SET_BIT(board->pieces[piece], to);

    }
    else
    {
        if(piece == w_king)
            board->castles[QC] = board->castles[KC] = 0;

        if(piece == b_king)
            board->castles[qc] = board->castles[kc] = 0;

        if(piece == w_rook && from == a1)
            board->castles[QC] = 0;

        if(piece == w_rook && from == h1)
            board->castles[KC] = 0;

        if(piece == b_rook && from == a8)
            board->castles[qc] = 0;

        if(piece == b_rook && from == h8)
            board->castles[kc] = 0;

        POP_BIT(board->occupied[both], from);
        POP_BIT(board->occupied[board->turn], from);
        POP_BIT(board->pieces[piece], from);
        POP_BIT(board->occupied[!board->turn], to);

        if (capture_piece != empty)
            POP_BIT(board->pieces[capture_piece], to);

        SET_BIT(board->occupied[both], to);
        SET_BIT(board->occupied[board->turn], to);
        SET_BIT(board->pieces[piece], to);


        if (prom_piece != empty)
        {
            enum piece pawn = board->turn == white ? w_pawn : b_pawn;
            printf("In promotion %d\n", prom_piece);
            POP_BIT(board->pieces[pawn], to);
            SET_BIT(board->pieces[prom_piece], to);
        }

    }
}
