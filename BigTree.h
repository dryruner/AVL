#ifndef BIGTREE_H
#define	BIGTREE_H

/*
 * 
Properties of B-Tree
    1) All leaves are at same level.
    2) A B-Tree is defined by the term minimum degree ‘t’..
    3) Every node except root must contain at least t-1 keys. Root may contain minimum 1 key.
    4) All nodes (including root) may contain at MOST  2t – 1 keys.
    5) Number of children of a node is equal to the number of keys in it plus 1.
    6) All keys of a node are sorted in increasing order. The child between two keys k1 and k2 contains all keys in range from k1 and k2
    7) B-Tree grows and shrinks from root which is unlike  Binary Search Tree that grow downward and also shrink from downward.
    8) Like other balanced Binary Search Trees, time complexity to search, insert and delete is O(Logn).
Source [http://www.geeksforgeeks.org/b-tree-set-1-introduction-2/]
 * 
 */
#include<iostream>
using namespace std;
 
// A BTree node
class BTreeNode
{
    int *keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
public:
    BTreeNode(int _t, bool _leaf);   // Constructor
 
    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int k);
 
    // A utility function to split the child y of this node. i is index of y in
    // child array C[].  The Child y must be full when this function is called
    void splitChild(int i, BTreeNode *y);
 
    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();
 
    // A function to search a key in subtree rooted with this node.
    BTreeNode *search(int k);   // returns NULL if k is not present.
 
// Make BTree friend of this so that we can access private members of this
// class in BTree functions
friend class BigTree;
};

class BigTree {
public:
    void BigMenu();
    
        // Constructor (Initializes tree as empty)
    BigTree(int _t)
    {  root = NULL;  t = _t; }
 
    // function to traverse the tree
    void traverse()
    {  if (root != NULL) root->traverse(); }
 
    // function to search a key in this tree
    BTreeNode* search(int k)
    {  return (root == NULL)? NULL : root->search(k); }
    
     // The main function that inserts a new key in this B-Tree
    void insert(int k);
    
private:
    BTreeNode *root; // Pointer to root node
    int t;  // Minimum degree

};

#endif	/* BIGTREE_H */

