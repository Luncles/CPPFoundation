//
// Created by Luncles Liu on 2023/7/27.
//

#ifndef CPPFOUNDATION_BINTREE_H
#define CPPFOUNDATION_BINTREE_H
#include <assert.h>
#include <iostream>

using KEY_VALUE = int;

// 数据结构与业务逻辑要分离，所以value要单独分出来
#define BSTREE_ENTITY(name, type) \
    struct name {                 \
        struct type* left;        \
        struct type* right;                          \
    }                                  \

    struct bstree_node {
        KEY_VALUE data;
        BSTREE_ENTITY(, bstree_node) bst;
    };

struct bstree {
    bstree_node* root;
};

struct bstree_node* bstree_create_node(KEY_VALUE key) {
    struct bstree_node* node = (struct bstree_node*)malloc(sizeof(struct bstree_node));
    if (node == nullptr) {
        assert(0);
    }
    node->data = key;
    node->bst.left = node->bst.right = nullptr;

    return node;
}

int brtree_insert(struct bstree* T, KEY_VALUE key) {
    if (T == nullptr) {
        assert(0);
    }

    if (T->root == nullptr) {
        T->root = bstree_create_node(key);
        return 0;
    }

    struct bstree_node* node = T->root;
    struct bstree_node* parent = T->root;
    while (node != nullptr) {
        parent = node;
        if (key < node->data) {
            node = node->bst.left;
        }
        else if (key > node->data) {
            node = node->bst.right;
        }
        else {
            std::cout << "the key already exist" << std::endl;
        }
    }

    struct bstree_node* newNode = bstree_create_node(key);
    if (key < parent->data) {
        parent->bst.left = newNode;
    }
    else {
        parent->bst.right = newNode;
    }

    return 0;
}
#endif //CPPFOUNDATION_BINTREE_H
