#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

typedef struct HashEntry {
    const char *key;
    int value;
    int occupied;
} HashEntry;

typedef struct HashTable {
    HashEntry *entries;
    size_t capacity;
    size_t size;
} HashTable;

void ht_init(HashTable *table, HashEntry *entries, size_t capacity);
int ht_put(HashTable *table, const char *key, int value);
int ht_get(const HashTable *table, const char *key, int *out_value);

#endif
