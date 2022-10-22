//
// Created by Danila Valkovets (dahnh33@gmail.com) on 19.10.2022.
//
#include "stdix_arraylist.h"

arraylist* arraylist_init() {
    return arraylist_init_manual(ARRAYLIST_DEFAULT_GROWTH_RATE, ARRAYLIST_DEFAULT_CAPACITY);
}

arraylist* arraylist_init_manual(const float rate, const size_t capacity) {
    if (rate < 1.5 || capacity < 2) return NULL;

    arraylist* list = malloc(sizeof *list);
    list->growth_rate = rate;
    list->capacity = capacity;
    list->array = malloc(list->capacity * sizeof *(list->array));

    if (list->array == NULL) return NULL;

    list->size = 0;
    return list;
}

arraylist* arraylist_init_from(const int* array, const size_t size) {
    arraylist* list = arraylist_init_manual(ARRAYLIST_DEFAULT_GROWTH_RATE, size);
    for (size_t i = 0; i < size; ++i) list->array[i] = array[i];
    list->size = size;
    return list;
}

inline int* arraylist_get_array(arraylist* list) {
    return list->array;
}

STATUS arraylist_ensure_capacity(arraylist* list, size_t new_size) {
    size_t capacity = list->capacity;
    if (new_size < capacity) return OK;
    while (capacity <= new_size) capacity = (size_t) ((float) capacity * list->growth_rate);
    list->array = realloc(list->array, capacity * sizeof *(list->array));
    if(list->array == NULL) return ALLOCATION_ERROR;
    list->capacity = capacity;
    return OK;
}

STATUS arraylist_add(arraylist* list, int value) {
    STATUS state;
    if((state = arraylist_ensure_capacity(list, ++(list->size))) != OK) return state;
    list->array[list->size - 1] = value;
    return OK;
}

STATUS arraylist_shift(int* array, const size_t offset, const size_t length) {
    memmove(array + offset,  array, length * sizeof *array);
    if (array != NULL) return OK;
    else return MEMORY_MOVE_ERROR;
}


STATUS arraylist_insert_at(arraylist* list, const size_t index, int value) {
    if (list->size == SIZE_MAX) return VARIABLE_OVERFLOW;
    STATUS state;
    if (index >= list->size) {
        if ((state = arraylist_ensure_capacity(list, index + 1)) != OK) return state;
        list->size = index + 1;
    } else if (list->array[index] != 0) {
        if ((state = arraylist_ensure_capacity(list, list->size + 1)) != OK) return state;
        arraylist_shift(list->array + index, 1, list->size - index);
        ++(list->size);
    } else {
        state = OK;
    }
    list->array[index] = value;
    return state;
}

STATUS arraylist_remove_at(arraylist* list, const size_t index) {
    if (list->size == 0) return OPERATION_NOT_ALLOWED;
    STATUS state;
    if ((state = arraylist_shift(list->array + index + 1, -1, list->size - index)) != OK) return state;
    list->size--;
    return OK;
}

STATUS arraylist_remove_duplicates(arraylist* list) {
    size_t i, j;
    for (i = 0, j = 0; ++j < list->size; ) {
        if (list->array[i] == list->array[j]) {
            j++;
            continue;
        }
        if (j != (++i+1)) list->array[i] = list->array[j];
    }
    list->size = i + 1;
}

void arraylist_clear(arraylist* list) {
    list->size = 0;
}

void arraylist_free(arraylist* list) {
    free(list->array);
    free(list);
}