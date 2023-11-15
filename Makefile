CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -pg

SRCS = main.c get_best_move.c make_move.c \
       piece_movement.c position_hash_table.c evalute_position.c \
       init_functions.c move_generation.c player_interface.c \
       zobrist_hashing.c

OBJS = $(SRCS:.c=.o)

all: my_program

my_program: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) my_program gmon.out

profile: my_program
	./my_program
	gprof my_program gmon.out

