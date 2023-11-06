#include<stdlib.h>
#include<stdio.h>
#include"chess_types.h"

uint32_t sqrt64(uint64_t r)
{
    uint64_t t, b, c = 0;

    for (b = 1ull << 62; b; b >>= 2)
    {
        t = c + b;
        c >>= 1;
        if (t <= r)
        {
            r -= t;
            c += b;
        }
    }
    return (uint32_t)c;
}

int find_nearest_prime_above(unsigned n)
{
    for(uint64_t c_r = n;;c_r++)
    {
        enum bool a = true;
        if(c_r % 6 == 1 || c_r % 6 == 5)
        {
            uint32_t n1 = sqrt64(c_r);
            for (int i = 2; i < n1; i++)
                if (!(c_r % i))
                {
                    a = false;
                    break;
                }

            if (a) return c_r;
        }
    }
}
enum bool find_item(HashTable *t, Board_hash zobrist_hash)
{
    int index = zobrist_hash % t->n;

    for (HashItem * i = t->array[index];i; i = i->next)
        if (i->zobrist_hash == zobrist_hash)
            return true;

    return false;
}

int position_occurrences(HashTable *t, Board_hash zobrist_hash)
{
    int index = zobrist_hash % t->n;

    for (HashItem * i = t->array[index];i; i = i->next)
        if (i->zobrist_hash == zobrist_hash)
            return i->times_seen;

    return 0;
}

enum bool create_table(HashTable *t, unsigned size)
{
    t->n = find_nearest_prime_above(size);
    t->used = 0;
    t->array = malloc(t->n * sizeof(HashItem *));
    if (t->array == NULL)
    {
        printf("ERROR CAN'T ALLOCATE MEMORY FOR TABLE DATA!!!\n");
        free(t);
        return false;
    }

    for(int i = 0;i < t->n;i++)
        t->array[i] = NULL;

    return true;
}
enum bool insert_item(HashTable *t, Board_hash zobrist_hash);
void destroy_table(HashTable *t);

enum bool rehash_table(HashTable *t)
{
    struct table new_table;
    if(!create_table(&new_table, 2 * t->n))
        return false;

    for (int i = 0; i < t->n; i++)
        for (HashItem * curr = t->array[i];curr; curr = curr->next)
            if(!insert_item(&new_table, curr->zobrist_hash))
            {
                printf("CAN'T INSERT ITEM WHILE REHASHING!!!\n");
                return false;
            }

    destroy_table(t);

    t->array = new_table.array;
    t->n = new_table.n;
    t->used = new_table.used;

    return true;
}

enum bool insert_item(HashTable *t, Board_hash zobrist_hash)
{
    int index = zobrist_hash % t->n;
    for (HashItem * i = t->array[index];i; i = i->next)
        if (i->zobrist_hash == zobrist_hash)
        {
            i->times_seen++;
            return true;
        }

    if(t->used == t->n)
    {
        rehash_table(t);
    }

    HashItem *new_item = malloc(sizeof(*new_item));
    if (!new_item)
    {
        printf("ERROR CAN'T ALLOCATE MEMORY FOR ITEM!!!\n");
        return false;
    }
    new_item->times_seen = 1;
    new_item->zobrist_hash = zobrist_hash;
    new_item->next = NULL;

    if(t->array[index])
    {
        HashItem *i = t->array[index];
        for(; i->next; i = i->next);
        i->next = new_item;

        return true;
    }

    t->array[index] = new_item;
    t->used++;

    return true;
}

enum bool remove_item(HashTable * t, Board_hash zobrist_hash)
{
    int index = zobrist_hash % t->n;

    for(HashItem *curr = t->array[index], *prev = NULL; curr ;prev = curr, curr = curr->next)
    {
        if(curr->zobrist_hash == zobrist_hash)
        {
            if(--curr->times_seen == 0)
            {
                if (!prev)
                {
                    t->array[index] = curr->next;

                    if (!curr->next)
                        t->used--;
                }
                else
                    prev->next = curr->next;

                free(curr);
            }

            return true;
        }
    }

    return false;
}

void destroy_table(HashTable *t)
{
    for (int i = 0; i < t->n; i++)
    {
        HashItem * curr = t->array[i];
        while (curr)
        {
            HashItem * next = curr->next;
            free(curr);
            curr = next;
        }
        t->array[i] = NULL;
    }
    t->n = t->used = 0;

    free(t->array);
}
