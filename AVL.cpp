/**
 @brief  An implementation of AVL Tree, including delete, insert, search(skipped cause AVL is one kind of BST)
 */

#include "AVL.h"
#include<iostream>
#include<stdio.h>

AVL* AVLTree::New_Node(KEY_TYPE key, AVL* lchild, AVL* rchild, int height) {
    AVL* p_avl = new AVL;
    p_avl->key = key;
    p_avl->lchild = lchild;
    p_avl->rchild = rchild;
    p_avl->height = height;
    return p_avl;
}

inline int AVLTree::getHeight(AVL* node) {
    return (node == NULL) ? -1 : node->height;
}

inline int AVLTree::max(int a, int b) {
    return a > b ? a : b;
}

/* RR(Y rotates to the right):

        k2                   k1
       /  \                 /  \
      k1   Z     ==>       X   k2
     / \                      /  \
    X   Y                    Y    Z
 */

/*
 Return which the root pointer(at a higher level) should point to
 */
AVL* AVLTree::RR_Rotate(AVL* k2) {
    AVL* k1 = k2->lchild;
    k2->lchild = k1->rchild;
    k1->rchild = k2;
    k2->height = max(getHeight(k2->lchild), getHeight(k2->rchild)) + 1;
    k1->height = max(getHeight(k1->lchild), k2->height) + 1;
    return k1;
}

/* LL(Y rotates to the left):

        k2                       k1
       /  \                     /  \
      X    k1         ==>      k2   Z
          /  \                /  \
         Y    Z              X    Y
 */
AVL* AVLTree::LL_Rotate(AVL* k2) {
    AVL* k1 = k2->rchild;
    k2->rchild = k1->lchild;
    k1->lchild = k2;
    k2->height = max(getHeight(k2->lchild), getHeight(k2->rchild)) + 1;
    k1->height = max(getHeight(k1->rchild), k2->height) + 1;
    return k1;
}



/* LR(B rotates to the left, then C rotates to the right):
      k3                         k3                       k2
     /  \                       /  \                     /  \
    k1   D                     k2   D                   k1   k3
   /  \         ==>           /  \        ==>          / \   / \
  A    k2                    k1   C                   A  B  C   D
      /  \                  /  \
     B    C                A    B
 */

/*
 Return which the root pointer should point to
 */
AVL* AVLTree::LR_Rotate(AVL* k3) {
    k3->lchild = LL_Rotate(k3->lchild);
    return RR_Rotate(k3);
}

/* RL(D rotates to the right, then C rotates to the left):

       k3                         k3                          k2
      /  \                       /  \                        /  \
     A    k1                    A    k2                     k3   k1 
         /  \       ==>             /  \         ==>       /  \  / \
        k2   B                     C    k1                A   C D   B
       /  \                            /  \
      C    D                          D    B 
 */
AVL* AVLTree::RL_Rotate(AVL* k3) {
    k3->rchild = RR_Rotate(k3->rchild);
    return LL_Rotate(k3);
}

/* return which the root pointer(at an outer/higher level) should point to,
   the root_node of AVL tree may change frequently during delete/insert,
   so the Root pointer should point to the REAL root node.
 */
AVL* AVLTree::Insert(AVL* root, KEY_TYPE key) {
    if (root == NULL)
        return (root = New_Node(key, NULL, NULL));
    else if (key < root->key)
        root->lchild = Insert(root->lchild, key);
    else //key >= root->key
        root->rchild = Insert(root->rchild, key);

    root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
    if (getHeight(root->lchild) - getHeight(root->rchild) == 2) {
        if (key < root->lchild->key)
            root = RR_Rotate(root);
        else
            root = LR_Rotate(root);
    } else if (getHeight(root->rchild) - getHeight(root->lchild) == 2) {
        if (key < root->rchild->key)
            root = RL_Rotate(root);
        else
            root = LL_Rotate(root);
    }
    return root;
}


/* return which the root pointer(at an outer/higher level) should pointer to,
   cause the root_node of AVL tree may change frequently during delete/insert,
   so the Root pointer should point to the REAL root node.
 */
AVL* AVLTree::Delete(AVL* root, KEY_TYPE key) {
    if (!root)
        return NULL;
    if (key == root->key) {
        if (root->lchild == NULL && root->rchild == NULL) {
            /* if the element is a leaf then we delete it and return the
             value. When the node that is being deleted is an intermediary node 
             then this value that is returned is the one we substitute the 
             original node's value for */
            AVL* temp = root;
            root = NULL;
            delete(temp);
            return root;
            
        } else if (root->lchild != NULL) {
            /* In this case we return substitute the node we want to delete
             with the biggest element of it's left sub-tree */
            AVL* temp = root->lchild;
            while (temp->rchild)
                temp = temp->rchild;
            /* replace the value */
            root->key = temp->key;
            /* Delete the node (successor node) that should be really deleted */
            root->lchild = Delete(root->lchild, temp->key);

        } else if (root->rchild != NULL) {
            /* if there is no left sub-tree then we get the smallest element from
               the right sub-tree */
            AVL* temp = root->rchild;
            while (temp->lchild)
                temp = temp->lchild;
            /* replace the value */
            root->key = temp->key;
            /* Delete the node (successor node) that should be really deleted */
            root->rchild = Delete(root->rchild, temp->key);
        }

    } else if (key < root->key)
        root->lchild = Delete(root->lchild, key);
    else
        root->rchild = Delete(root->rchild, key);
    
    /* we get the new height and rotate the tree if necessary. Note that this
       part of the code gets called at every recursive step */
    root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
    
    if (getHeight(root->rchild) - getHeight(root->lchild) == 2) {
        if (getHeight(root->rchild->rchild) >= getHeight(root->rchild->lchild))
            root = LL_Rotate(root);
        else
            root = RL_Rotate(root);
    } else if (getHeight(root->lchild) - getHeight(root->rchild) == 2) {
        if (getHeight(root->lchild->lchild) >= getHeight(root->lchild->rchild))
            root = RR_Rotate(root);
        else
            root = LR_Rotate(root);
    }
    return root;
}

void AVLTree::InOrder(AVL* root) {
    if (root == NULL)
        return;
    InOrder(root->lchild);
    std::cout << root->key << "  ";
    InOrder(root->rchild);
}

void AVLTree::PreOrder(AVL* root) {
    if (root == NULL)
        return;
    std::cout << root->key << "  ";
    PreOrder(root->lchild);
    PreOrder(root->rchild);
}

void AVLTree::PostOrder(AVL* root) {
    if (root == NULL)
        return;
    PostOrder(root->lchild);
    PostOrder(root->rchild);
    std::cout << root->key << "  ";
}

void AVLTree::Display(AVL* ptr, int level) {
    int i;
    if (ptr != NULL) {
        AVLTree::Display(ptr->rchild, level + 1);
        printf("\n");
        for (i = 0; i < level; i++)
            std::cout << "        ";
        std::cout << ptr->key << "------- ";
        Display(ptr->lchild, level + 1);
    }
}
/* Initialization of the AVL Tree to pass to the menu*/
void AVLTree::AVLmenu(){
        AVL* root = NULL;
	int vector[] = {15,6,18,3,7,17,20,2,4,13,9};
	const int length = sizeof(vector)/sizeof(int);
	for(int i = 0; i< length;i++)
		root = AVLTree::Insert(root, vector[i]);
        AVLmenu(root);
}

/* The AVL Tree menu per se */
void AVLTree::AVLmenu(AVL* root){
    using namespace std;
    int choice, item;
    while (1)
    {
        //if (system("CLS")) system("clear");
        cout << endl;
        cout<<"---------------------"<<endl;
        cout<<"AVL Tree Implementation"<<endl;
        cout<<"---------------------"<<endl;
        cout<<"\t1.Insert Element into the tree"<<endl;
        cout<<"\t2.Display AVL Tree"<<endl;
        cout<<"\t3.InOrder"<<endl;
        cout<<"\t4.PreOrder"<<endl;
        cout<<"\t5.PostOrder"<<endl;
        cout<<"\t6.Delete Item from tree"<<endl;
        cout<<"\t7.Exit"<<endl;
        cout<<"\tEnter your Choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter value to be inserted: ";
            cin>>item;
            root = AVLTree::Insert(root, item);
            break;
        case 2:
            if (root == NULL)
            {
                cout<<"Tree is Empty"<<endl;
                continue;
            }
            cout<<"AVL Tree:"<<endl;
            AVLTree::Display(root, 0);
            break;
        case 3:
            cout<<"InOrder:"<<endl;
            AVLTree::InOrder(root);
            cout<<endl;
            break;
        case 4:
            cout<<"PreOrder:"<<endl;
            AVLTree::PreOrder(root);
            cout<<endl;
            break;
        case 5:
            cout<<"PostOrder:"<<endl;
            AVLTree::PostOrder(root);    
            cout<<endl;
            break;
        case 6:
            cout<<"Enter the value to be deleted: ";
            cin>>item;
            root = AVLTree::Delete(root, item);
            break;
        case 7:
            return;    
            break;
        default:
            cout<<"Invalid Option"<<endl;
        }
    }
}
