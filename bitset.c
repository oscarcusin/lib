#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "bitset.h"

typedef unsigned int bitset_data_t;

struct bitset {
    size_t size;
    bitset_data_t data[];
};

bitset * bitset_new(size_t size) {
    size_t elems = (size - 1) / (sizeof(bitset_data_t) * CHAR_BIT) + 1;
    bitset * bs = malloc(sizeof(bitset) + elems * sizeof(bitset_data_t));
    if (!bs) return NULL;
    memset(bs->data, 0, elems * sizeof(bitset_data_t));
    bs->size = size;
    return bs;
}

bitset * bitset_new_filled(size_t size) {
    size_t elems = (size - 1) / (sizeof(bitset_data_t) * CHAR_BIT) + 1;
    bitset * bs = malloc(sizeof(bitset) + elems * sizeof(bitset_data_t));
    if (!bs) return NULL;
    memset(bs->data, 0xff, (elems - 1) * sizeof(bitset_data_t));
    bitset_data_t mask = 0;
    for (size_t i = 0; i < size % (sizeof(bitset_data_t) * CHAR_BIT); i++) {
        mask |= ((bitset_data_t) 1 << i);
    }
    bs->data[elems - 1] = mask;
    bs->size = size;
    return bs;
}

void bitset_free(bitset * bs) {
    if (!bs) return;
    free(bs);
}

size_t bitset_size(bitset * bs) {
    if (!bs) return 0;
    return bs->size;
}

size_t bitset_count(bitset * bs) {
    if (!bs) return 0;
    size_t elems = (bs->size - 1) / (sizeof(bitset_data_t) * CHAR_BIT) + 1;
    size_t count = 0;
    for (size_t i = 0; i < elems; i++) {
        bitset_data_t data = bs->data[i];
        while (data) {
            count += data & 1;
            data >>= 1;
        }
    }
    return count;
}

void bitset_set(bitset * bs, size_t index) {
    if (!bs || index >= bs->size) return;
    size_t elem = index / (sizeof(bitset_data_t) * CHAR_BIT);
    bitset_data_t mask = ((bitset_data_t) 1 << (index % (sizeof(bitset_data_t) * CHAR_BIT)));
    bs->data[elem] |= mask;
}

void bitset_clear(bitset * bs, size_t index) {
    if (!bs || index >= bs->size) return;
    size_t elem = index / (sizeof(bitset_data_t) * CHAR_BIT);
    bitset_data_t mask = ((bitset_data_t) 1 << (index % (sizeof(bitset_data_t) * CHAR_BIT)));
    bs->data[elem] &= ~mask;
}

void bitset_union(bitset * bs1, bitset * bs2) {
    if (!bs1 || !bs2 || bs1->size != bs2->size) return;
    size_t elems = (bs1->size - 1) / (sizeof(bitset_data_t) * CHAR_BIT) + 1;
    for (size_t i = 0; i < elems; i++) {
        bs1->data[i] |= bs2->data[i];
    }
}

void bitset_intersection(bitset * bs1, bitset * bs2) {
    if (!bs1 || !bs2 || bs1->size != bs2->size) return;
    size_t elems = (bs1->size - 1) / (sizeof(bitset_data_t) * CHAR_BIT) + 1;
    for (size_t i = 0; i < elems; i++) {
        bs1->data[i] &= bs2->data[i];
    }
}

int bitset_get(bitset * bs, size_t index) {
    if (!bs || index >= bs->size) return 0;
    return bs->data[index / (sizeof(bitset_data_t) * CHAR_BIT)] & ((bitset_data_t) 1 << (index % (sizeof(bitset_data_t) * CHAR_BIT))) ? 1 : 0;
}
