#include <stdlib.h>
#include <string.h>
#include "deque.h"

#define INITIAL_CAPACITY 16

struct deque {
    size_t front, elem_size, size, capacity;
    char * data;
};

deque * deque_new(size_t elem_size) {
    deque * deq = malloc(sizeof(deque));
    if (!deq) return NULL;
    deq->data = malloc(INITIAL_CAPACITY * elem_size);
    if (!deq->data) {
        free(deq);
        return NULL;
    }
    deq->front = 0;
    deq->elem_size = elem_size;
    deq->size = 0;
    deq->capacity = INITIAL_CAPACITY;
    return deq;
}

deque * deque_new_from(size_t elem_size, void * data, size_t size) {
    deque * deq = malloc(sizeof(deque));
    if (!deq) return NULL;
    deq->data = malloc(size * elem_size);
    if (!deq->data) {
        free(deq);
        return NULL;
    }
    deq->front = 0;
    deq->elem_size = elem_size;
    deq->size = size;
    deq->capacity = size;
    memcpy(deq->data, data, size * elem_size);
    return deq;
}

deque * deque_copy(deque * deq) {
    if (!deq) return NULL;
    deque * copy = malloc(sizeof(deque));
    if (!copy) return NULL;
    copy->data = malloc(deq->capacity * deq->elem_size);
    if (!copy->data) {
        free(copy);
        return NULL;
    }
    if (deq->front + deq->size <= deq->capacity) {
        memcpy(copy->data, deq->data + deq->front, deq->size * deq->elem_size);
    } else {
        memcpy(copy->data, deq->data + deq->front, (deq->capacity - deq->front) * deq->elem_size);
        memcpy(copy->data + (deq->capacity - deq->front) * deq->elem_size, deq->data, (deq->size - (deq->capacity - deq->front)) * deq->elem_size);
    }
    return copy;
}

void deque_free(deque * deq) {
    if (!deq) return;
    if (deq->data) free(deq->data);
    free(deq);
}

size_t deque_size(deque * deq) {
    if (!deq) return 0;
    return deq->size;
}

int _deque_double_capacity(deque * deq) {
    char * new_data = malloc(deq->capacity * 2 * deq->elem_size);
    if (!new_data) return 0;
    if (deq->front + deq->size <= deq->capacity) {
        memcpy(new_data, deq->data + deq->front * deq->elem_size, deq->size * deq->elem_size);
    } else {
        memcpy(new_data, deq->data + deq->front * deq->elem_size, (deq->capacity - deq->front) * deq->elem_size);
        memcpy(new_data + (deq->capacity - deq->front) * deq->elem_size, deq->data, (deq->size - (deq->capacity - deq->front)) * deq->elem_size);
    }
    free(deq->data);
    deq->front = 0;
    deq->capacity *= 2;
    deq->data = new_data;
    return 1;
}

void * deque_push_front(deque * deq, void * item) {
    if (!deq || !item) return NULL;
    if (deq->size >= deq->capacity) {
        if (!_deque_double_capacity(deq)) return NULL;
    }
    if (deq->front) deq->front--;
    else deq->front = deq->capacity - 1;
    void * new = deq->data + deq->front * deq->elem_size;
    memcpy(new, item, deq->elem_size);
    deq->size++;
    return new;
}

void * deque_push_back(deque * deq, void * item) {
    if (!deq || !item) return NULL;
    if (deq->size >= deq->capacity) {
        if (!_deque_double_capacity(deq)) return NULL;
    }
    void * new = deq->data + (deq->front + deq->size) % deq->capacity * deq->elem_size;
    memcpy(new, item, deq->elem_size);
    deq->size++;
    return new;
}

void deque_pop_front(deque * deq) {
    if (!deq || !deq->size) return;
    deq->size--;
    deq->front = (deq->front + 1) % deq->capacity;
}

void deque_pop_back(deque * deq) {
    if (!deq || !deq->size) return;
    deq->size--;
}

void * deque_peek_front(deque * deq) {
    if (!deq || !deq->size) return NULL;
    return deq->data + deq->front * deq->elem_size;
}

void * deque_peek_back(deque * deq) {
    if (!deq || !deq->size) return NULL;
    return deq->data + ((deq->front + deq->size - 1) % deq->capacity) * deq->elem_size;
}
