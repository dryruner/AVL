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

/* Clase que va a representar a un nodo del arbol */
class BTreeNode {
    
private:
    int * keys; // Arreglo de numeros en el nodo
    int degree; // Define el grado del nodo (este es compartido por todos los nodos del arbol)
    BTreeNode ** children; // Un arreglo de punters hacia los nodos hijos
    int number_keys; //numero actual de numeros (keys)  que se encuentran en el nodo
    bool leaf; // Es un nodo hoja o no
    
public:
    BTreeNode(int _t, bool _leaf); // Constructor

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // A function to search a key in subtree rooted with this node.
    BTreeNode *search(int k); // returns NULL if k is not present.

    // A function that returns the index of the first key that is greater
    // or equal to k
    int findKey(int k);

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int k);

    // A utility function to split the child y of this node. i is index
    // of y in child array C[].  The Child y must be full when this
    // function is called
    void splitChild(int i, BTreeNode *y);

    // A wrapper function to remove the key k in subtree rooted with
    // this node.
    void remove(int k);

    // A function to remove the key present in idx-th position in
    // this node which is a leaf
    void removeFromLeaf(int idx);

    // A function to remove the key present in idx-th position in
    // this node which is a non-leaf node
    void removeFromNonLeaf(int idx);

    // A function to get the predecessor of the key- where the key
    // is present in the idx-th position in the node
    int getPred(int idx);

    // A function to get the successor of the key- where the key
    // is present in the idx-th position in the node
    int getSucc(int idx);

    // A function to fill up the child node present in the idx-th
    // position in the C[] array if that child has less than t-1 keys
    void fill(int idx);

    // A function to borrow a key from the C[idx-1]-th node and place
    // it in C[idx]th node
    void borrowFromPrev(int idx);

    // A function to borrow a key from the C[idx+1]-th node and place it
    // in C[idx]th node
    void borrowFromNext(int idx);

    // A function to merge idx-th child of the node with (idx+1)th child of
    // the node
    void merge(int idx);

    // Make BTree friend of this so that we can access private members of
    // this class in BTree functions
    friend class BigTree;
};

class BigTree {
 private:
    BTreeNode *root; // Pointer to root node
    int tree_degree; // Minimum degree

public:
   static void BigMenu();

    // Constructor (Initializes tree as empty)

    BigTree(int _degree) {
        root = NULL;
        tree_degree = _degree;
    }

    void traverse() {
        if (root != NULL) root->traverse();
    }

    // function to search a key in this tree

    BTreeNode* search(int k) {
        return (root == NULL) ? NULL : root->search(k);
    }

    // The main function that inserts a new key in this B-Tree
    void insert(int k);

    // The main function that removes a new key in thie B-Tree
    void remove(int k);




};

#endif	/* BIGTREE_H */

