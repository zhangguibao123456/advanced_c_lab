#include "hash_table.h"

#include <string.h>

static size_t fnv1a(const char *text) {
    size_t hash = 1469598103934665603ULL;
    while (*text != '\0') {
        hash ^= (unsigned char)*text++;
        hash *= 1099511628211ULL;
    }
    return hash;
}

void ht_init(HashTable *table, HashEntry *entries, size_t capacity) {
    table->entries = entries;
    table->capacity = capacity;
    table->size = 0;
    for (size_t i = 0; i < capacity; ++i) {
        entries[i].key = 0;
        entries[i].value = 0;
        entries[i].occupied = 0;
    }
}

int ht_put(HashTable *table, const char *key, int value) {
    if (table->size * 2U >= table->capacity) {
        return 0;
    }

    size_t index = fnv1a(key) % table->capacity;
    for (size_t probe = 0; probe < table->capacity; ++probe) {
        HashEntry *entry = &table->entries[index];
        if (!entry->occupied || strcmp(entry->key, key) == 0) {
            table->size += entry->occupied ? 0U : 1U;
            entry->key = key;
            entry->value = value;
            entry->occupied = 1;
            return 1;
        }
        index = (index + 1U) % table->capacity;
    }
    return 0;
}

int ht_get(const HashTable *table, const char *key, int *out_value) {
    size_t index = fnv1a(key) % table->capacity;
    for (size_t probe = 0; probe < table->capacity; ++probe) {
        const HashEntry *entry = &table->entries[index];
        if (!entry->occupied) {
            return 0;
        }
        if (strcmp(entry->key, key) == 0) {
            *out_value = entry->value;
            return 1;
        }
        index = (index + 1U) % table->capacity;
    }
    return 0;
}
