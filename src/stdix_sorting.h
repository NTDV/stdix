//
// Created by Danila Valkovets (dahnh33@gmail.com) on 12.12.2022.
//

#ifndef STDIX_STDIX_SORTING_H
#define STDIX_STDIX_SORTING_H

#include <string.h>
#include "stdix_dynamicarray.h"

typedef struct {
    string fullName;
    char group[7];
    float averageMark;
} STUDENT; // REMOVE THE STRUCT FROM CODE -> use pointer arithmetic istead

typedef int (*COMPARATOR)(void const*, void const*);
typedef void (*SORTER)(void* base, size_t length, size_t size, COMPARATOR cmp);

void swap(void* a, void* b, size_t size);
void dynamicarray_sort(dynamicarray* array, SORTER algorithm, COMPARATOR comparator);

void ix_qsort_(void* base, size_t low, size_t high, size_t size, COMPARATOR comparator);
void ix_qsort(void* base, size_t length, size_t size, COMPARATOR comparator);
void ix_pairinsertion_sort(void* base, size_t length, size_t size, COMPARATOR comparator);

#endif //STDIX_STDIX_SORTING_H
