//
// Created by Danila Valkovets (dahnh33@gmail.com) on 12.11.2022.
//

#ifndef STDIX_DYNAMICARRAY_H
#define STDIX_DYNAMICARRAY_H

#include <stddef.h>
#include <stdint.h>
#include "stdix.h"

typedef struct {
    double* array;
    size_t size;
} dynamicarray;

dynamicarray* dynamicarray_init();
dynamicarray* dynamicarray_init_manual(size_t initial_capacity);
dynamicarray* dynamicarray_init_from(const double* array, size_t size);
STATUS dynamicarray_insert_at(dynamicarray* array, size_t index, double value);
STATUS dynamicarray_remove_at(dynamicarray* array, size_t index);
void dynamicarray_free(dynamicarray* array);

#endif //STDIX_DYNAMICARRAY_H
