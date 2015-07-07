#include "RedBlack.h"
#include <stdio.h>
#include <iostream>
#include <assert.h>

/* Returns a pointer to the node which is the grandparent of n */
node* RedBlack::Grandparent(node* n){
    if(n->parent != NULL)
        return n->parent->parent;
    else 
        return NULL;
}

/* Returns a pointer to n's brother. If n has no brother then returns NULL */
node* RedBlack::Sibling(node* n){
    node* parent = n->parent;
    if(parent == NULL) return NULL;
    
    if(parent->left == n)
        return parent->right;
    
    else if(parent->right == n)
        return parent->left;
}

/* Returns a pointer to n's uncle (n's parent's brother). If n has no uncle
 * then it returns NULL */
node* RedBlack::Uncle(node* n){
    node* parent = n->parent;
    node* grandparent = Grandparent(n);
    if(parent == NULL || grandparent == NULL) return NULL;
    
    if(grandparent->left == parent)
        return grandparent->right;
    
    else if(grandparent->right == parent)
        return grandparent->left;
}

/*
 * This method is used to aid the rotations of the nodes. It replaces 
 * the old node 'oldno' with the new node 'newno'.
 */
void RedBlack::replace_node(node* oldno, node* newno){
    //if oldno is root    
    if (oldno->parent == NULL)
    {
        this->root = newno;
    }
    else
    {   
        //if oldno is a left child then newno will be set as oldno's parent left
        //child, or right in case oldno was right child.
        if (oldno == oldno->parent->left)
            oldno->parent->left = newno;
        else
            oldno->parent->right = newno;
    }
    if (newno != NULL)
    {
        newno->parent = oldno->parent;
    }
}

/*  Rotate to the right
        k2                   k1
       /  \                 /  \
      k1   Z     ==>       X   k2
     / \                      /  \
    X   Y                    Y    Z
  
 Changes the tree structure.
 */
void RedBlack::Right_Rotate(node* k2){
    node* k1 = k2->left;
    replace_node(k2, k1);
    k2->left = k1->right;
    if (k1->right != NULL)
    {
        k1->right->parent = k2;
    }
    k1->right = k2;
    k2->parent = k1;
}


/* Rotate to the left
        k2                       k1
       /  \                     /  \
      X    k1         ==>      k2   Z
          /  \                /  \
         Y    Z              X    Y
 Changes the tree structure
 */
void RedBlack::Left_Rotate(node* k2){
    node* k1 = k2->right;
    replace_node(k2, k1);
    k2->right = k1->left;
    if (k1->left != NULL)
    {
        k1->left->parent = k2;
    }
    k1->left = k2;
    k2->parent = k1;
}

/* If it's NULL then it means it's a leaf, so it's color is BLACK */
color RedBlack::node_color(node* n){
    return n == NULL ? BLACK : n->color;
}

/*Verify properties [rules]
 *  See RedBlack.h for a list of all the properties
 */
void RedBlack::verify_properties(){
    verify_property_1(this->root);
    verify_property_2();
    /* propery 3 is not verified since it states that
        'All leaves (NIL) are black'. */
    verify_property_4(this->root);
    verify_property_5(this->root);
}

/*
 * Verifies (for every node in the tree) that property 1 is not broken.
 * Property 1:
 *      "A node is either red or black"
 */
void RedBlack::verify_property_1(node* root){
    assert (node_color(root) == RED || node_color(root) == BLACK);
    if (root == NULL)
        return;
    verify_property_1(root->left);
    verify_property_1(root->right);
}

/*
 * Verifies that property 2 is not broken.
 * Property 2:
 *      "The root is black"
 */
void RedBlack::verify_property_2(){
    assert (node_color(this->root) == BLACK);
}

/*
 * Verifies (for every node in the tree) that property 4 is not broken.
 * Property 4:
 *      "Every red node must have two black child nodes, 
 *      and therefore it must have a black parent."
 */
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

/*
 * Verifies (for every node in the tree) that property 5 is not broken.
 * Property 5:
 *      "Every path from a given node to any of its descendant NIL 
 *       nodes contains the same number of black nodes."
 */
void RedBlack::verify_property_5(node* root){
    int black_count_path = -1;
    verify_property_5_rec(root, 0, &black_count_path);
}

/*
 * A helper function which does the actual verification of property 5. It's a 
 * recursive method, all it's running 'instances' share the same value of 'path_black_count'
 * since it's a pointer.
 *    Parameters
 *      node* n: Is the node that we are testing in a given recursive call. 
 *      int black_count: It's the number of black nodes in a given path.
 *      int* path_black_count: Is a pointer that specifies which value of 'black_count'
 *                             should every path have. It's initial value is -1 and
 *                             the first recursive function to finish sets it's value.
 */
void RedBlack::verify_property_5_rec(node* n, int black_count, int* path_black_count){
    if (node_color(n) == BLACK)
    {
        //if n is color black then we add 1 to the black count of the path.
        black_count++;
    }
    //if n is NULL (which also means it's a leaf)
    if (n == NULL)
    {
        //if 'path_black_count' has value -1 it means that no other recursive path
        //has yet finished it's execution and that the actual recusive path is 
        //the first to reach this point.
        if (*path_black_count == -1)
        {
            //since our black_count is the same as every other recursive path ought to
            //get to then we set 
            *path_black_count = black_count;
        }
        //If path_black_count is not -1 it means that another recursive path has 
        //already specified a path_black_count. If our black_count is different,
        //then it means that not every path has the same number of black nodes.
        else if(black_count != *path_black_count)
        {
            //this will always stops the program, since the only way that this part
            //gets to be executed is that 'black_count != *path_black_count'
            assert (black_count == *path_black_count);
        }
        return;
    }
    
    verify_property_5_rec(n->left,  black_count, path_black_count);
    verify_property_5_rec(n->right, black_count, path_black_count);
}


/* 
 * Insertion is the same as in a normal binary tree. This is an iterative 
 * insertion method, however this same thing can also be done recursively 
 * (see AVL.cpp's Insert() for an example). At the end it calls 'insert_case1()'
 * which will start a chain of functions that will fix any problems created
 * because of the insertion, after that it will call 'verify_cases()' that will
 * check that every property of the tree has not been broken.
 */
void RedBlack::Insert(int _key){
    
    rbtree_node* node_insert = new rbtree_node();
    //new nodes are always inserted as RED nodes.
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
            // if the node already exists then we return since there can
            //be no repeated values in a binary tree.
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

/*
 * Checks if n is root, if it is then it's color will be changed to BLACK. If it's
 * not then it continues with 'insert_case2()'
 */
void RedBlack::insert_case1(node* n){
    if (n->parent == NULL)
        n->color = BLACK;
    else
        insert_case2(n);
}

/*
 * We know that n is RED, so if n's parent is BLACK everything is in order 
 * and there is no sense in continuing with the 'checking chain'. If the parent
 * is not BLACK then continues with 'insert_case3()'
 */
void RedBlack::insert_case2(node* n){
    if (node_color(n->parent) == BLACK)
        return;
    else
        insert_case3(n);
}

/*
 * We already know that n's parent is neither NULL nor BLACK, so now we check if 
 * n's uncle is RED, if it is we color both the UNCLE and the PARENT BLACK and we
 * also color the grandparent RED, at this point we know that from n's grandparent 
 * to n every property is consistent but we don't know if changing the grandparent's
 * color to red caused any problems so we start the 'checking chain' again but this 
 * time we are interested in checking n's grandparent. 
 * If n's uncle is not RED we go on to 'insert_case4()'
 */
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

/*
 * At this point we know that:
 *      n is RED
 *      n's parent is not NULL, 
 *      n's parent is colored RED
 *      n's uncle is colored BLACK
 * So now we need to rotate the tree to make the properties consistent again. This
 * rotation consists in rotating n's parent once and n's grandparent once. 
 * In 'insert_case4()' n's parent is rotated and then (after the rotation)
 * n is set to point to it's parent and we go on to 'insert_case5()'
 */
void RedBlack::insert_case4(node* n){
    //if n is a right child and n's parent is a left child we rotate left
    //       Gp(B)                     Gp(B)
    //      /                          /
    //  Pa(R)           ==>         n(R)
    //      \                       /
    //      n(R)                 Pa(R)
    if (n == n->parent->right && n->parent == Grandparent(n)->left)
    {
        Left_Rotate(n->parent);
        n = n->left; //point to parent
    }
    
    //if n is a left child and n's parent is a right child we rotate right
    //       Gp(B)                     Gp(B)
    //            \                        \
    //            Pa(R)           ==>       n(R)
    //            /                             \
    //         n(R)                             Pa(R)
    else if (n == n->parent->left && n->parent == Grandparent(n)->right)
    {
        Right_Rotate(n->parent);
        n = n->right; //point to parent 
    }
    insert_case5(n);
}

/*
 * This method performs the second rotation, but this time it rotates n's grandparent.
 * But before rotating n's parent's color is set to BLACK and n's grandparent's color
 * is set to RED.
 */
void RedBlack::insert_case5(node* n){
    n->parent->color = BLACK;
    Grandparent(n)->color = RED;
    
    //if n is a left child and n's parent is a left child we rotate RIGHT
    //       Gp(R)                
    //      /                       Pa(B)  
    //    Pa(B)           ==>      /    \
    //    /                      n(R)   Gp(R)
    //  n(R)                    
    if (n == n->parent->left && n->parent == Grandparent(n)->left)
    {
        Right_Rotate(Grandparent(n));
    }
        
    //if n is a right child and n's parent is a right child we rotate LEFT
    //       Gp(R)                
    //           \                        Pa(B)  
    //          Pa(B)         ==>        /    \
    //             \                   n(R)   Gp(R)
    //             n(R)              
    else
    {
        //this is the only other possible case so we 'assert' instead of use a conditional
        assert (n == n->parent->right && n->parent == Grandparent(n)->right);
        Left_Rotate(Grandparent(n));
    }
}

/*
 * This method is in charge of displaying the tree in a tree form.
 */
void RedBlack::Display(node* ptr, int level) {
    int i;
    if (ptr != NULL) {
        RedBlack::Display(ptr->right, level + 1);
        printf("\n");
        for (i = 0; i < level; i++)
            std::cout << "        ";
        if(node_color(ptr) == BLACK)
            std::cout << "<" << ptr->key << "> ---- ";
        else
            std::cout << ptr->key << "------ ";
        RedBlack::Display(ptr->left, level + 1);
    }
}

void RedBlack::RBMenu(){
    using namespace std;
    RedBlack* tree = new RedBlack();
    
    int choice, item;
    while (1)
    {
        cout << endl;
        cout<<"---------------------"<<endl;
        cout<<"RB Tree Implementation"<<endl;
        cout<<"---------------------"<<endl;
        cout<<"\t1.Insert Element into the tree"<<endl;
        cout<<"\t2.Display AVL Tree"<<endl;
        cout<<"\t3.Delete Item from tree"<<endl;
        cout<<"\t4.Exit"<<endl;
        cout<<"\tEnter your Choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter value to be inserted: ";
            cin>>item;
            tree->RedBlack::Insert(item);
            break;
        case 2:
            if (tree->root == NULL)
            {
                cout<<"Tree is Empty"<<endl;
                continue;
            }
            cout<<"RB Tree:"<<endl;
            tree->RedBlack::Display(tree->root,0);
            break;
        case 3:
            cout<<"Enter the value to be deleted: ";
            cin>>item;
            //
            break;
        case 4:
            return;    
            break;
        default:
            cout<<"Invalid Option"<<endl;
        }
    }
}
