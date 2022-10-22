//
// Created by Danila Valkovets (dahnh33@gmail.com) on 19.10.2022.
//

#ifndef STDIX_ARRAYLIST_H
#define STDIX_ARRAYLIST_H

#include <stddef.h>
#include <stdint.h>
#include "stdix.h"

#define ARRAYLIST_DEFAULT_CAPACITY 10
#define ARRAYLIST_DEFAULT_GROWTH_RATE 1.5f

typedef struct {
    float growth_rate;
    int* array;
    size_t capacity;
    size_t size;
} arraylist;

arraylist* arraylist_init();
arraylist* arraylist_init_manual(float growth_rate, size_t initial_capacity);
arraylist* arraylist_init_from(const int* array, size_t size);
int* arraylist_get_array(arraylist* list);
STATUS arraylist_add(arraylist* list, int value);
STATUS arraylist_insert_at(arraylist* list, size_t index, int value);
STATUS arraylist_remove_at(arraylist* list, size_t index);
STATUS arraylist_remove_duplicates(arraylist* list);


#endif //STDIX_ARRAYLIST_H
