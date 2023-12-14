#include <stdio.h>
#include <limits.h>
#include "chess_types.h"
#include "evalute_position.h"
#include "get_best_move.h"
#include "init_functions.h"
#include "make_move.h"
#include "move_generation.h"
#include "piece_movement.h"
#include "player_interface.h"
#include "zobrist_hashing.h"
#include "position_hash_table.h"


int main()
{
    HashTable t;
    create_table(&t, 100);

    ChessBoard board = parse_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
    
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();
   
    MoveList list = init_move_list();
    
    print_chess_board(&board);
    
    for(float i = 100;i <= 3280; i+=100)
    {
        float f = i / 3280;
        printf("%f\n", f);
        long long v = (float)easy_endgame(&board) / f;
        printf("%lli\n", v);
    }

    return 0;
    int depth = 4;
    enum color turn = board.turn;
    for(int i = 0;i < 40;i++)
    {
        long long eval;
        int move;
        board.turn == white ? printf("WHITE\n") : printf("BLACK\n");
        
        if(!min_max(&board, &tbls, &keys, &t, &move, &eval, depth, LLONG_MIN, LLONG_MAX, depth))
        {
                (eval < 0) ? printf("BLACK WINS\n") : printf("WHITE WINS\n");    
                return 0;
        }
            
        print_move(move);
        play_move(move, &board);
        printf("EVALUATION: %lli", eval);            

        print_chess_board(&board);
        board.turn  = !board.turn;

    }
    
    return 0;
}
