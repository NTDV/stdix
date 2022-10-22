//
// Created by Danila Valkovets (dahnh33@gmail.com) on 20.10.2022.
//

#ifndef STDIX_LINKEDTREE_H
#define STDIX_LINKEDTREE_H

#include <stddef.h>
#include <stdint.h>
#include "stdix.h"

typedef char NODE_COLOR;
#define BLACK ((char) 0)
#define RED   ((char) 1)

typedef struct linkedtree_node linkedtree_node;

struct linkedtree_node {
    NODE_COLOR color;
    linkedtree_node* parent;
    linkedtree_node* right;
    linkedtree_node* left;
    linkedtree_node* next;
    void* value;
};


linkedtree_node* linkedtree_node_init(void* value);
linkedtree_node* linkedtree_node_insert_children(linkedtree_node* node, linkedtree_node* children);
void linkedtree_node_inorder(linkedtree_node* node, void (*fun)(void*));
void linkedtree_node_foreach(linkedtree_node* node, void (*fun)(void*));

typedef struct {
    linkedtree_node* root;
    linkedtree_node* first;
    linkedtree_node* last;
    size_t count;
} linkedtree;

linkedtree* linkedtree_init();
linkedtree* linkedtree_init_with(void* value);
linkedtree* linkedtree_init_from(void* array, size_t size);
void linkedtree_add(linkedtree* tree, void* value);
void linkedtree_rotate_right(linkedtree* tree, linkedtree_node* node);
void linkedtree_rotate_left(linkedtree* tree, linkedtree_node* node);
void linkedtree_rebalance_at(linkedtree* tree, linkedtree_node* node);
void linkedtree_inorder(linkedtree* tree, void (*fun)(void*));
void linkedtree_foreach(linkedtree* tree, void (*fun)(void*));

#endif //STDIX_LINKEDTREE_H
