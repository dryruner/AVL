#ifndef REDBLACK_H
#define	REDBLACK_H
enum color { RED, BLACK };

typedef struct rbtree_node
{
    enum color color;
    int key;
    rbtree_node *left, *right, *parent;
}* node;

class RedBlack {
private:
    rbtree_node root;
    int compare(int a, int b);  //returns 0 if equal or a>b ? 1 : -1
    node* grandparent(node* n);
    node* sibling(node* n);
    node* uncle(node* n);
    bool verify_case1(node* node);
    bool verify_case2(node* node);
    bool verify_case3(node* node);
    node new_node(color, int key, rbtree_node* left, rbtree_node* right, rbtree_node* parent);
public:
    void Insert(int _key);
    void Delete(int _key);

};

#endif	/* REDBLACK_H */

