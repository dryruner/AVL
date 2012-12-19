#ifndef __AVL_H__
#define __AVL_H__

typedef int KEY_TYPE;

/* no parent pointer */
typedef struct AVL{
	KEY_TYPE key;
	int height;
	struct AVL* lchild;
	struct AVL* rchild;
}AVL;

AVL* New_Node(KEY_TYPE key, AVL* lchild, AVL* rchild, int height = 0);
inline int getHeight(AVL* node);
/*
 Return which the root pointer(at a higher level) should point to
 */
AVL* RR_Rotate(AVL* k2);
AVL* LL_Rotate(AVL* k2);
/*
 Return which the root pointer should point to
 */
AVL* LR_Rotate(AVL* k3);

/* RL(D rotates to the right, then C rotates to the left):*/
AVL* RL_Rotate(AVL* k3);


AVL* Insert(AVL* root, KEY_TYPE key);
AVL* Delete(AVL* root, KEY_TYPE key);
void InOrder(AVL* root);


#endif
