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
    create_table(&t, 10000);

	ChessBoard board = parse_FEN("2k5/4P3/8/8/4K3/8/8/8 w - - 0 1");
    
    LookupTable tbls = fill_lookup_table();
    Keys keys = init_random_keys();
   
    MoveList list = init_move_list();
    
    print_chess_board(&board);
    
    int depth = 4;
    enum color turn = board.turn;
    for(int i = 0;i < 10;i++)
    {
        long long eval;
        int move;
        board.turn == white ? printf("WHITE\n") : printf("BLACK\n");
		printf("%d\n", board.turn);
        
		if (!min_max(&board, &tbls, &keys, &t, &move, &eval, depth, LLONG_MIN, LLONG_MAX, depth)) {
			printf("Could not find best move, terminating.\n");
			break;
		}
        
        print_move(move);
        play_move(move, &board);
        /* printf("EVALUATION: %lli", eval); */            
        printf("===============================================================================\n");

        print_chess_board(&board);
        board.turn  = !board.turn;

    }
    
    return 0;
}
