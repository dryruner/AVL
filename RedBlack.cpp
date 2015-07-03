#include "RedBlack.h"
#include <stdio.h>
#include <assert.h>


node* RedBlack::Grandparent(node* n){
    if(n->parent != NULL)
        return n->parent->parent;
    else 
        return NULL;
}

node* RedBlack::Sibling(node* n){
    node* parent = n->parent;
    if(parent == NULL) return NULL;
    
    if(parent->left == n)
        return parent->right;
    
    else if(parent->right == n)
        return parent->left;
}

node* RedBlack::Uncle(node* n){
    node* parent = n->parent;
    node* grandparent = Grandparent(n);
    if(parent == NULL || grandparent == NULL) return NULL;
    
    if(grandparent->left == parent)
        return grandparent->right;
    
    else if(grandparent->right == parent)
        return grandparent->left;
}

void RedBlack::Right_Rotate(node* k2){
    node* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
}

void RedBlack::Left_Rotate(node* k2){
    node* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
}

/* If it's NULL then it means it's a leaf, so it's color is BLACK */
color RedBlack::node_color(node* n){
    return n == NULL ? BLACK : n->color;
}

//Verify properties [rules]
void RedBlack::verify_properties(){
    verify_property_1(this->root);
    verify_property_2(this->root);
    verify_property_4(this->root);
    verify_property_5(this->root);
}

void RedBlack::verify_property_1(node* root){
    assert (node_color(root) == RED || node_color(root) == BLACK);
    if (root == NULL)
        return;
    verify_property_1(root->left);
    verify_property_1(root->right);
}

void RedBlack::verify_property_2(node* root){
    assert (node_color(root) == BLACK);
}

void RedBlack::verify_property_4(node* root){
    if (node_color(root) == RED)
    {
        assert (node_color(root->left) == BLACK);
        assert (node_color(root->right) == BLACK);
        assert (node_color(root->parent) == BLACK);
    }
    if (root == NULL)
        return;
    verify_property_4(root->left);
    verify_property_4(root->right);
}

//The number of blacks from the root to a leaf must be the same for every path
void RedBlack::verify_property_5(node* root){
    int black_count_path = -1;
    verify_property_5_rec(root, 0, &black_count_path);
}
void RedBlack::verify_property_5_rec(node* n, int black_count, int* path_black_count){
    if (node_color(n) == BLACK)
    {
        black_count++;
    }
    if (n == NULL)
    {
        if (*path_black_count == -1)
        {
            *path_black_count = black_count;
        }
        else
        {
            assert (black_count == *path_black_count);
        }
        return;
    }
    verify_property_5_rec(n->left,  black_count, path_black_count);
    verify_property_5_rec(n->right, black_count, path_black_count);
}


/* Insertion is the same as in a normal binary tree */
void RedBlack::Insert(int _key){
    rbtree_node* node_insert = new rbtree_node();
    node_insert->color = RED;
    node_insert->key = _key;
    if (this->root == NULL)
    {
        this->root = node_insert;
    }
    else
    {
        node* n = this->root;
        //iterative insert
        while (1)
        {
            if (n->key == node_insert->key)
            {
                return;
            }
            else if (node_insert->key < n->key)
            {
                if (n->left == NULL)
                {
                    n->left = node_insert;
                    break;
                }
                else
                {
                    n = n->left;
                }
            }
            else
            {
                assert (node_insert->key > n->key);
                if (n->right == NULL)
                {
                    n->right = node_insert;
                    break;
                }
                else
                {
                    n = n->right;
                }
            }
        }
        node_insert->parent = n;
    }
    insert_case1(node_insert);
    verify_properties();
}

void RedBlack::insert_case1(node* n){
    if (n->parent == NULL)
        n->color = BLACK;
    else
        insert_case2(n);
}
void RedBlack::insert_case2(node* n){
    if (node_color(n->parent) == BLACK)
        return;
    else
        insert_case3(n);
}
void RedBlack::insert_case3(node* n){
    if (node_color(Uncle(n)) == RED)
    {
        n->parent->color = BLACK;
        Uncle(n)->color = BLACK;
        Grandparent(n)->color = RED;
        insert_case1(Grandparent(n));
    }
    else
    {
        insert_case4(n);
    }
}
void RedBlack::insert_case4(node* n){
    if (n == n->parent->right && n->parent == Grandparent(n)->left)
    {
        Left_Rotate(n->parent);
        n = n->left;
    }
    else if (n == n->parent->left && n->parent == Grandparent(n)->right)
    {
        Right_Rotate(n->parent);
        n = n->right;
    }
    insert_case5(n);
}
void RedBlack::insert_case5(node* n){
    n->parent->color = BLACK;
    Grandparent(n)->color = RED;
    if (n == n->parent->left && n->parent == Grandparent(n)->left)
    {
        Right_Rotate(Grandparent(n));
    }
    else
    {
        assert (n == n->parent->right && n->parent == Grandparent(n)->right);
        Left_Rotate(Grandparent(n));
    }
}

void RedBlack::Delete(int _key){
    
}