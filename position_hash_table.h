#include "chess_types.h"

#ifndef CHESS_BITBOARD_MAIN_POSITION_HASH_TABLE_H
#define CHESS_BITBOARD_MAIN_POSITION_HASH_TABLE_H

enum bool find_item(struct table* t, Board_hash zobrist_hash);
enum bool create_table(HashTable *t, unsigned size);
enum bool rehash_table(HashTable *t);
enum bool insert_item(HashTable *t, Board_hash zobrist_hash);
enum bool remove_item(HashTable *t, Board_hash zobrist_hash);
int position_occurrences(HashTable *t, Board_hash zobrist_hash);
void destroy_table(HashTable *t);

#endif //CHESS_BITBOARD_MAIN_POSITION_HASH_TABLE_H
