#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>

typedef struct deque deque;

// Allocates a new deque with an element size of ELEM_SIZE bytes.
// Returns a pointer to the deque on success, or NULL on failure.
deque * deque_new(size_t elem_size);

// Allocates a new deque with an element size of ELEM_SIZE bytes and initializes it with the data in DATA.
// Returns a pointer to the deque on success, or NULL on failure.
deque * deque_new_from(size_t elem_size, void * data, size_t size);

// Allocates a new deque with the same element size, size, and capacity as DEQ, and copies the data from DEQ.
// Returns a pointer to the deque on success, or NULL on failure.
deque * deque_copy(deque * deq);

// Frees the deque DEQ.
void deque_free(deque * deq);

// Returns the size of the deque DEQ.
size_t deque_size(deque * deq);

// Adds ITEM to the front of the deque DEQ.
// Copies the memory pointed to by ITEM into the deque.
// Returns a pointer to the added item on success, NULL on failure.
void * deque_push_front(deque * deq, void * item);

// Adds ITEM to the back of the deque DEQ.
// Copies the memory pointed to by ITEM into the deque.
// Returns a pointer to the added item on success, NULL on failure.
void * deque_push_back(deque * deq, void * item);

// Removes the frontmost element of the deque DEQ.
void deque_pop_front(deque * deq);

// Removes the backmost element of the deque DEQ.
void deque_pop_back(deque * deq);

// Returns a pointer to the frontmost element of the deque DEQ, or NULL on failure.
void * deque_peek_front(deque * deq);

// Returns a pointer to the backmost element of the deque DEQ, or NULL on failure.
void * deque_peek_back(deque * deq);

#endif
