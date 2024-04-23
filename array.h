#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

typedef struct array array;

// Allocates a new array with an element size of ELEM_SIZE.
// Returns a pointer to the array on success, or NULL on failure.
array * array_new(size_t elem_size);

// Allocates a new array with an element size of ELEM_SIZE and intializes it with the data in DATA.
// Returns a pointer to the array on success, or NULL on failure.
array * array_new_from(size_t elem_size, void * data, size_t size);

// Allocates a new array with the same element size, size, and capacity as ARR, and copies the data from ARR.
// Returns a pointer to the array on success, or NULL on failure.
array * array_copy(array * arr);

// Frees the array ARR.
void array_free(array * arr);

// Returns the size of the array ARR.
size_t array_size(array * arr);

// Returns the index of ITEM in the array ARR, or SIZE_MAX on failure.
// ITEM must be a pointer to an element in the array.
size_t array_index(array * arr, void * item);

// Returns a pointer to the data in the array ARR, or NULL on failure.
void * array_data(array * arr);

// Returns a pointer to the first element in the array ARR, or NULL on failure.
void * array_begin(array * arr);

// Returns a pointer to the element after the last element in the array ARR, or NULL on failure.
// This pointer should not be dereferenced.
void * array_end(array * arr);

// Returns a pointer to the next element after ITEM in the array ARR, or NULL on failure.
// ITEM must be a pointer to an element in the array.
void * array_next(array * arr, void * item);

// Searches the array ARR for an element that matches KEY using the CMP function, using a linear search.
void * array_search(array * arr, int (*cmp) (const void *, const void *), void * key);

// Searches the array ARR for an element that matches KEY using the CMP function, using a binary search.
// The array must be sorted before calling this function.
void * array_search_sorted(array * arr, int (*cmp) (const void *, const void *), void * key);

// Inserts ITEM at INDEX in the array ARR, shifting the rest of the items to the right.
// Copies the memory pointed to by ITEM into the array.
// Returns a pointer to the inserted item on success, NULL on failure.
void * array_insert(array * arr, size_t index, void * item);

// Adds ITEM to the end of the array ARR.
// Copies the memory pointed to by ITEM into the array.
// Returns a pointer to the added item on success, NULL on failure.
void * array_add(array * arr, void * item);

// Inserts ITEM into the array ARR in sorted order using the CMP function, shifting the rest of the items to the right.
// Copies the memory pointed to by ITEM into the array.
// Returns a pointer to the inserted item on success, NULL on failure.
void * array_insert_sorted(array * arr, int (*cmp) (const void *, const void *), void * item);

// Removes the element at INDEX from the array ARR, shifting the rest of the items to the left.
// Returns 0 on success, -1 on failure.
int array_remove_at(array * arr, size_t index);

// Removes ITEM from the array ARR, shifting the rest of the items to the left.
// ITEM must be a pointer to an element in the array.
// Returns 0 on success, -1 on failure.
int array_remove(array * arr, void * item);

// Sorts the array ARR using the CMP function.
// Returns 0 on success, -1 on failure.
int array_sort(array * arr, int (*cmp) (const void *, const void *));

#endif
