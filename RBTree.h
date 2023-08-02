//
// Created by Luncles Liu on 2023/8/2.
//

#ifndef CPPFOUNDATION_RBTREE_H
#define CPPFOUNDATION_RBTREE_H
#define RED 1
#define BLACK 2
using KEY_VALUE = int;

typedef struct _rbtree_node {
    unsigned char color;
    struct _rbtree_node* right;
    struct _rbtree_node* left;
    struct _rbtree_node* parent;
    KEY_VALUE key;
    void* value
}rbtree_node;

typedef struct _rbtree {
    struct rbtree_node* root;
    struct rbtree_node* nil;
}rbtree;

void rbtreeLeftRotate(rbtree* T, rbtree_node* x) {
    rbtree_node* y = x->right;

    // y是x的右子树，现在左旋，将y作为根
    // 第一，二步：将x变为y的左子树，调换parent
    x->right = y->left;
    if (y->left != T->nil) {
        y->left->parent = x;
    }

    // 第三步，将y作为父节点
    y->parent = x->parent;
    // 判断x是不是根节点
    if (x->parent == T->nil) {
        T->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    // 第五，六步，调整x，y的指针
    y->left = x;
    x->parent = y;
}

void rbtreeRightRotate(rbtree* T, rbtree_node* x) {
    rbtree_node* y = x->left;
    if (y->right != T->nil) {
        y->right->parent = x;
    }
    x->left = y->right;

    y->parent = x->parent;
    if (x->parent == T->nil) {
        T->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    y->right = x;
    x->parent = y;
}

// 插入后调整
void rbtree_insert_fixup(rbtree* T, rbtree_node* z) {
    // 如果是在黑节点下插入，不用调整
    while (z->parent->color == RED) {
        // 插入的父节点是祖父节点的左子节点
        if (z->parent == z->parent->parent->left) {
            // 第一种情况，叔节点是红色的，要变色
            rbtree_node *y = z->parent->parent->right;
            if (y->color == RED) {
                // 父节点变黑色，叔节点变黑色，祖父节点变红色，要检查曾祖父节点是不是红色
                z->parent->color = BLACK;
                y->color = BLACK;
                y->parent->color = RED;

                // 更新z，向上检查
                z = z->parent->parent;
            }
            else {
                // 第二种情况，叔节点是黑色，且插入的节点是父节点的右子节点
                if (z == z->parent->right) {
                    // 先左旋，整合成第三种情况的样子一起处理
                    z = z->parent;
                    rbtreeLeftRotate(T, z);
                }

                // 第三种情况，叔节点是黑色的，且插入的节点是父节点的左子节点，变色就行
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtreeRightRotate(T, z->parent->parent);
            }
        }
        else {
            rbtree_node *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                y->color = BLACK;

                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rbtreeRightRotate(T, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtreeLeftRotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

void rbtree_insert(rbtree* T, rbtree_node* z) {
    rbtree_node *x = T->root;
    rbtree_node *y = T->nil;

    while (x != T->nil) {
        y = x;
        if (z->value < x->value) {
            x = x->left;
        }
        else if (z->value > x->value) {
            x = x->right;
        }
        else {
            printf("exist\n");
        }
    }

    z->parent = y;
    if (y == T->nil) {
        T->root = z;
    }
    else if (y->value > z->value) {
        y->left = z;
    }
    else {
        y->right = z;
    }

    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;

}
#endif //CPPFOUNDATION_RBTREE_H
