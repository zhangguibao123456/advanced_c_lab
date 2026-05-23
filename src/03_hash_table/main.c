#include "hash_table.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    HashEntry entries[16];
    HashTable table;
    ht_init(&table, entries, 16);

    if (!ht_put(&table, "ch4", 100) || !ht_put(&table, "temp", 25) ||
        !ht_put(&table, "humidity", 62)) {
        return EXIT_FAILURE;
    }

    int value = 0;
    if (!ht_get(&table, "temp", &value)) {
        return EXIT_FAILURE;
    }

    printf("temp=%d size=%zu\n", value, table.size);
    return value == 25 && table.size == 3U ? EXIT_SUCCESS : EXIT_FAILURE;
}
