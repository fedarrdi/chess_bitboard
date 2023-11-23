CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
DEBUG_FLAGS = -g -O0 # Debugging flags: -g for debugging symbols, -O0 to disable optimization

SRCS = main.c get_best_move.c make_move.c \
       piece_movement.c position_hash_table.c evalute_position.c \
       init_functions.c move_generation.c player_interface.c \
       zobrist_hashing.c

OBJS = $(SRCS:.c=.o)

all: my_program

my_program: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@ # Include debug flags for object file creation

clean:
	rm -f $(OBJS) my_program

profile:
	./my_program
	gprof my_program

debug: CFLAGS += $(DEBUG_FLAGS) # Add debug flags to CFLAGS for compiling with debug symbols
debug: clean all # Clean and recompile with debug flags

.PHONY: all clean profile debug

