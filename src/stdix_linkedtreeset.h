//
// Created by Danila Valkovets (dahnh33@gmail.com) on 21.10.2022.
//

#ifndef STDIX_LINKEDTREESET_H
#define STDIX_LINKEDTREESET_H

#include "stdix.h"
#include "stdix_linkedtree.h"

typedef struct {
    linkedtree* tree;
} linkedtreeset;

linkedtreeset* linkedtreeset_init();
linkedtreeset* linkedtreeset_init_with(void* value);
linkedtreeset* linkedtreeset_init_from(void* array, size_t size);
void linkedtreeset_add(linkedtreeset* set, void* value);
void linkedtreeset_foreach(linkedtreeset* set, void (*fun)(void*));
int* linkedtreeset_to_array(linkedtreeset* set);
void linkedtreeset_free(linkedtreeset* set);

#endif //STDIX_LINKEDTREESET_H
