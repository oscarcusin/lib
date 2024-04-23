#ifndef BITSET_H
#define BITSET_H

#include <stddef.h>

typedef struct bitset bitset;

// Allocates a new bitset of size SIZE, and initializes all bits to 0.
// Returns a pointer to the bitset on success, or NULL on failure.
bitset * bitset_new(size_t size);

// Allocates a new bitset of size SIZE, and initializes all bits to 1.
// Returns a pointer to the bitset on success, or NULL on failure.
bitset * bitset_new_filled(size_t size);

// Allocates a new bitset of size SIZE, and copies the data from BS.
// Returns a pointer to the bitset on success, or NULL on failure.
bitset * bitset_copy(bitset * bs);

// Frees the bitset BS.
void bitset_free(bitset * bs);

// Returns the size of the bitset BS.
size_t bitset_size(bitset * bs);

// Returns the number of bits set in the bitset BS.
size_t bitset_count(bitset * bs);

// Sets the bit at INDEX in the bitset BS.
void bitset_set(bitset * bs, size_t index);

// Clears the bit at INDEX in the bitset BS.
void bitset_clear(bitset * bs, size_t index);

// Performs a bitwise OR operation between BS1 and BS2.
// Modifies BS1 to contain the result.
void bitset_union(bitset * bs1, bitset * bs2);

// Performs a bitwise AND operation between BS1 and BS2.
// Modifies BS1 to contain the result.
void bitset_intersection(bitset * bs1, bitset * bs2);

// Returns 1 if the bit at INDEX is set, 0 otherwise.
int bitset_get(bitset * bs, size_t index);

#endif
