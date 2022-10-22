//
// Created by Danila Valkovets (dahnh33@gmail.com) on 20.10.2022.
//
#include "stdix_linkedtree.h"

linkedtree_node* linkedtree_node_init(void* value) {
    linkedtree_node* node = malloc(sizeof(linkedtree_node));
    node->color = RED;
    node->parent = NULL;
    node->right = NULL;
    node->left = NULL;
    node->next = NULL;
    node->value = value;
    return node;
}

linkedtree_node* linkedtree_node_insert_children(linkedtree_node* node, linkedtree_node* children) {
    if (node == NULL) return children;

    if (*((int *)(node->value)) <= *((int *)(children->value))) {
        node->right = linkedtree_node_insert_children(node->right, children);
        node->right->parent = node;
    } else if (*((int *)(node->value)) > *((int *)(children->value))) {
        node->left = linkedtree_node_insert_children(node->left, children);
        node->left->parent = node;
    }

    return node;
}

linkedtree* linkedtree_init() {
    linkedtree* tree = malloc(sizeof(linkedtree));
    tree->root = NULL;
    tree->first = NULL;
    tree->last = NULL;
    tree->count = 0;
}

linkedtree* linkedtree_init_with(void* value) {
    linkedtree* tree = linkedtree_init();
    linkedtree_add(tree, value);
    return tree;
}

linkedtree* linkedtree_init_from(void* array, size_t size) {
    linkedtree* tree = linkedtree_init();
    for (size_t i = 0; i < size; ++i) linkedtree_add(tree, &((int *) array)[i]);
    return tree;
}

void linkedtree_add(linkedtree* tree, void* value) {
    linkedtree_node* node = linkedtree_node_init(value);
    if (tree->first == NULL) tree->last = (tree->first = node);
    else tree->last = (tree->last->next = node);
    ++(tree->count);
    tree->root = linkedtree_node_insert_children(tree->root, node);
    linkedtree_rebalance_at(tree, node);
}

void linkedtree_rotate_right(linkedtree* tree, linkedtree_node* node) {
    linkedtree_node* left = node->left;
    node->left = left->right;

    if (node->left) node->left->parent = node;
    left->right = node->right;

    if (!node->parent) tree->root = left;
    else if (node == node->parent->left) node->parent->left = left;
    else node->parent->right = left;

    left->right = node;
    node->parent = left;
}

void linkedtree_rotate_left(linkedtree* tree, linkedtree_node* node) {
    linkedtree_node* right = node->right;
    node->right = right->left;

    if (node->right) node->right->parent = node;
    right->parent = node->parent;

    if (!node->parent) tree->root = right;
    else if (node == node->parent->left) node->parent->left = right;
    else node->parent->right = right;

    right->left = node;
    node->parent = right;
}

void linkedtree_rebalance_at(linkedtree* tree, linkedtree_node* node) {
    linkedtree_node* parent = NULL;
    linkedtree_node* grandparent = NULL;

    while ((node != tree->root) && (node->color != BLACK) && (node->parent->color == RED)) {
        grandparent = (parent = node->parent)->parent;
        if (parent == grandparent->left) {                          /// A: Parent is left child of grandparent
            linkedtree_node* uncle = grandparent->right;
            if (uncle != NULL && uncle->color == RED) {             /// 1: Uncle is red
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {                        /// 2: Node is right child of parent
                    linkedtree_rotate_left(tree, parent);
                    node = parent;
                    parent = node->parent;
                }
                linkedtree_rotate_right(tree, grandparent);    /// 3: Node is left child of parent
                NODE_COLOR color = parent->color;
                parent->color = grandparent->color;
                grandparent->color = color;
                node = parent;
            }
        } else {                                                    /// B: Parent is right child of grandparent
            linkedtree_node* uncle = grandparent->left;
            if ((uncle != NULL) && (uncle->color == RED)) {         /// 1: Uncle is red
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {                         /// 2: Node is left child of parent
                    linkedtree_rotate_right(tree, parent);
                    node = parent;
                    parent = node->parent;
                }
                linkedtree_rotate_left(tree, grandparent);     /// 3: Node is right child of parent
                NODE_COLOR color = parent->color;
                parent->color = grandparent->color;
                grandparent->color = color;
                node = parent;
            }
        }
    }
    tree->root->color = BLACK;
}

void linkedtree_inorder(linkedtree* tree, void (*fun)(void*)) {
    linkedtree_node_inorder(tree->root, fun);
}

void linkedtree_node_inorder(linkedtree_node* node, void (*fun)(void*)) {
    if (node == NULL) return;
    linkedtree_node_inorder(node->left, fun);
    fun(node->value);
    linkedtree_node_inorder(node->right, fun);
}

void linkedtree_foreach(linkedtree* tree, void (*fun)(void*)) {
    if (tree->first != NULL) linkedtree_node_foreach(tree->first, fun);
}

void linkedtree_node_foreach(linkedtree_node* node, void (*fun)(void*)) {
    fun(node->value);
    if (node->next != NULL) linkedtree_node_foreach(node->next, fun);
}