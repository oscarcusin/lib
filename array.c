#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "array.h"

#define INITIAL_CAPACITY 16

struct array {
    size_t elem_size, size, capacity;
    char * data;
};

array * array_new(size_t elem_size) {
    array * arr = malloc(sizeof(array));
    if (!arr) return NULL;
    arr->data = malloc(INITIAL_CAPACITY * elem_size);
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    arr->elem_size = elem_size;
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    return arr;
}

array * array_new_from(size_t elem_size, void * data, size_t size) {
    array * arr = malloc(sizeof(array));
    if (!arr) return NULL;
    arr->data = malloc(size * elem_size);
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    arr->elem_size = elem_size;
    arr->size = size;
    arr->capacity = size;
    memcpy(arr->data, data, size * elem_size);
    return arr;
}

array * array_copy(array * arr) {
    if (!arr) return NULL;
    array * copy = malloc(sizeof(array));
    if (!copy) return NULL;
    copy->data = malloc(arr->capacity * arr->elem_size);
    if (!copy->data) {
        free(copy);
        return NULL;
    }
    copy->elem_size = arr->elem_size;
    copy->size = arr->size;
    copy->capacity = arr->capacity;
    memcpy(copy->data, arr->data, arr->size * arr->elem_size);
    return copy;
}

void array_free(array * arr) {
    if (!arr) return;
    if (arr->data) free(arr->data);
    free(arr);
}

size_t array_size(array * arr) {
    if (!arr) return 0;
    return arr->size;
}

size_t array_index(array * arr, void * item) {
    if (!arr || !item) return SIZE_MAX;
    size_t index = ((char *) item - arr->data) / arr->elem_size;
    if (index >= arr->size) return SIZE_MAX;
    return index;
}

void * array_data(array * arr) {
    if (!arr) return NULL;
    return arr->data;
}

void * array_begin(array * arr) {
    return array_data(arr);
}

void * array_end(array * arr) {
    if (!arr) return NULL;
    return arr->data + arr->size * arr->elem_size;
}

void * array_next(array * arr, void * item) {
    if (!arr || !item) return NULL;
    return (char *) item + arr->elem_size;
}

void * array_search(array * arr, int (*cmp) (const void *, const void *), void * key) {
    if (!arr || !cmp || !key) return NULL;
    for (void * item = array_begin(arr); item != array_end(arr); item = array_next(arr, item)) {
        if (!cmp(item, key)) return item;
    }
    return NULL;
}

static size_t binary_search(array * arr, int (*cmp) (const void *, const void *), void * key) {
    size_t left = 0, right = arr->size;
    while (left < right) {
        size_t mid = (left + right) / 2;
        void * p = arr->data + mid * arr->elem_size;
        int comparison = cmp(key, p);
        if (comparison < 0) right = mid;
        else if (comparison > 0) left = mid + 1;
        else return mid;
    }
    return left;
}

void * array_search_sorted(array * arr, int (*cmp) (const void *, const void *), void * key) {
    if (!arr || !cmp || !key) return NULL;
    size_t i = binary_search(arr, cmp, key);
    return cmp(arr->data + i * arr->elem_size, key) ? NULL : arr->data + i * arr->elem_size;
}

void * array_insert(array * arr, size_t index, void * item) {
    if (!arr || !item || index > arr->size) return NULL;
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * arr->elem_size);
        if (!arr->data) return NULL;
    }
    memmove(arr->data + (index + 1) * arr->elem_size, arr->data + index * arr->elem_size, (arr->size - index) * arr->elem_size);
    void * new = arr->data + index * arr->elem_size;
    memcpy(new, item, arr->elem_size);
    arr->size++;
    return new;
}

void * array_add(array * arr, void * item) {
    if (!arr || !item) return NULL;
    return array_insert(arr, arr->size, item);
}

void * array_insert_sorted(array * arr, int (*cmp) (const void *, const void *), void * item) {
    if (!arr || !cmp || !item) return NULL;
    size_t index = binary_search(arr, cmp, item);
    return array_insert(arr, index, item);
}

int array_remove_at(array * arr, size_t index) {
    if (!arr || index >= arr->size) return -1;
    memmove(arr->data + index * arr->elem_size, arr->data + (index + 1) * arr->elem_size, (arr->size - index - 1) * arr->elem_size);
    arr->size--;
    return 0;
}

int array_remove(array * arr, void * item) {
    return array_remove_at(arr, array_index(arr, item));
}

int array_sort(array * arr, int (*cmp) (const void *, const void *)) {
    if (!arr) return -1;
    qsort(arr->data, arr->size, arr->elem_size, cmp);
    return 0;
}
