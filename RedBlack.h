#ifndef REDBLACK_H
#define	REDBLACK_H

/* 
 * Rules of a Red/Black tree 
 *      1. A node is either red or black.
 *      2. The root is black.
 *      3. All leaves (NIL) are black. All leaves are of the same color as the root.
 *      4. Every red node must have two black child nodes, and therefore it must have a black parent.
 *      5. Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes.
 * [source: https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Properties]
 */
enum color {
    RED, BLACK
};

typedef struct rbtree_node {
    enum color color;
    int key;
    rbtree_node *left, *right, *parent;
} node;

class RedBlack {
private:
    rbtree_node* root;
    node* Grandparent(node* n);
    node* Sibling(node* n);
    node* Uncle(node* n);
    void Right_Rotate(node* k2);
    void Left_Rotate(node* k2);
    color node_color(node* n);
    void replace_node(node* oldno, node* newno);

    //verify rules are not broken
    void verify_properties();
    void verify_property_1(node* root);
    void verify_property_2();
    void verify_property_4(node* root);
    void verify_property_5(node* root);
    void verify_property_5_rec(node* n, int black_count, int* path_black_count);

    //insert steps
    void insert_case1(node* n);
    void insert_case2(node* n);
    void insert_case3(node* n);
    void insert_case4(node* n);
    void insert_case5(node* n);
    
public:
    static void RBMenu();
    void Insert(int _key);
    void Display(node* ptr, int level);

};

#endif	/* REDBLACK_H */

