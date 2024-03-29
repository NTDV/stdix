//
// Created by Danila Valkovets (dahnh33@gmail.com) on 12.11.2022.
//
#include "stdix_dynamicarray.h"

dynamicarray* dynamicarray_init() {
    dynamicarray* array = malloc(sizeof *array);
    array->size = 0;
    array->array = malloc(array->size * sizeof *(array->array));

    if (array->array == NULL) return NULL;
    return array;
}

STATUS dynamicarray_ensure_capacity(dynamicarray* array, size_t new_size) {
    if (new_size < array->size) return OK;
    array->array = realloc(array->array, new_size * sizeof *(array->array));
    if(array->array == NULL) return ALLOCATION_ERROR;
    return OK;
}

STATUS dynamicarray_shift(void** array, const size_t offset, const size_t length) {
    memmove(array + offset,  array, length * sizeof *array);
    if (array != NULL) return OK;
    else return MEMORY_MOVE_ERROR;
}


STATUS dynamicarray_insert_at(dynamicarray* array, size_t index, void* value) {
    if (array->size == SIZE_MAX) return VARIABLE_OVERFLOW;
    STATUS state;
    if (index >= array->size) {
        if ((state = dynamicarray_ensure_capacity(array, array->size + 1)) != OK) return state;
        array->array[array->size] = value;
        ++(array->size);
    } else {
        if ((state = dynamicarray_ensure_capacity(array, array->size + 1)) != OK) return state;
        dynamicarray_shift(array->array + index, 1, array->size - index);
        array->array[index] = value;
        ++(array->size);
    }
    state = OK;
    return state;
}

STATUS dynamicarray_remove_at(dynamicarray* array, size_t index) {
    if (array->size == 0) return OPERATION_NOT_ALLOWED;
    if (index >= array->size) return INVALID_ARGUMENT;
    STATUS state;
    if ((state = dynamicarray_shift(array->array + index + 1, -1, array->size - index - 1)) != OK) return state;
    array->size--;
    return OK;
}

void dynamicarray_free(dynamicarray* array) {
    if (array != NULL) {
        free(array->array);
        free(array);
    }
}