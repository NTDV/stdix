//
// Created by Danila Valkovets (dahnh33@gmail.com) on 21.10.2022.
//
#include "stdix_linkedtreeset.h"

linkedtreeset* linkedtreeset_init() {
    linkedtreeset* set = malloc(sizeof(linkedtreeset*));
    set->tree = linkedtree_init();
    return set;
}

linkedtreeset* linkedtreeset_init_with(void* value) {
    linkedtreeset* set = malloc(sizeof(linkedtreeset*));
    set->tree = linkedtree_init_with(value);
    return set;
}

linkedtree_node* linkedtreeset_linkedtree_node_insert_children(linkedtree_node* node,
                                                               linkedtree_node* children) {
    if (node == NULL) return children;

    if (*((int *)(node->value)) > *((int *)(children->value))) {
        linkedtree_node* new_node =
                linkedtreeset_linkedtree_node_insert_children(node->right, children);
        if (new_node == NULL) return NULL;

        node->right = new_node;
        node->right->parent = node;
    } else if (*((int *)(node->value)) < *((int *)(children->value))) {
        linkedtree_node* new_node =
                linkedtreeset_linkedtree_node_insert_children(node->left, children);
        if (new_node == NULL) return NULL;

        node->left = new_node;
        node->left->parent = node;
    } else return NULL;

    return node;
}

void linkedtreeset_linkedtree_add(linkedtree* tree, void* value) {
    linkedtree_node* node = linkedtree_node_init(value);
    linkedtree_node* new_root =
            linkedtreeset_linkedtree_node_insert_children(tree->root, node);
    if (new_root == NULL) {
        free(node);
        return;
    }

    if (tree->first == NULL) tree->last = (tree->first = node);
    else tree->last = (tree->last->next = node);
    tree->root = new_root;
    ++(tree->count);

    linkedtree_rebalance_at(tree, node);
}

linkedtreeset* linkedtreeset_init_from(void* array, size_t size) {
    linkedtreeset* set = malloc(sizeof(linkedtreeset*));
    set->tree = linkedtree_init();
    for (size_t i = 0; i < size; ++i) linkedtreeset_linkedtree_add(set->tree, &((int *) array)[i]);
    return set;
}

int* linkedtreeset_to_array(linkedtreeset* set) {
    int* array = malloc(set->tree->count * sizeof(int));
    linkedtree_node* node = set->tree->first;
    for (size_t i = 0; i < set->tree->count; ++i) {
        if (node == NULL) return array;
        array[i] = *((int *)(node->value));
        node = node->next;
    }
    return array;
}

void linkedtreeset_add(linkedtreeset* set, void* value) {
    linkedtreeset_linkedtree_add(set->tree, value);
}

void linkedtreeset_foreach(linkedtreeset* set, void (*fun)(void*)) {
    linkedtree_foreach(set->tree, fun);
}

void linkedtreeset_free(linkedtreeset* set) {
    if (set != NULL) {
        linkedtree_free(set->tree);
        free(set);
    }
}