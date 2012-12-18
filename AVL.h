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

AVL* New_Node(KEY_TYPE key, AVL* lchild, AVL* rchild, int height = -1);
inline int getHeight(AVL* node);
/* RR(Y rotates to the right):

		k2                   k1
	   /  \           		/  \
	  k1   Z     ==>       X   k2
	 / \                      /  \
    X   Y                    Y    Z
*/
/*
 Return which the root pointer(at a higher level) should point to
 */
AVL* RR_Rotate(AVL* k2);

/* LL(Y rotates to the left):

      k2                       k1
	 /  \                     /  \
	X    k1         ==>      k2   Z
		/  \                /  \
	   Y    Z              X    Y
 */
AVL* LL_Rotate(AVL* k2);

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
AVL* LR_Rotate(AVL* k3);

/* RL(D rotates to the right, then C rotates to the left):

       k3                         k3                          k2
	  /  \                       /  \                        /  \
	 A    k1                    A    k2                     k3   k1 
	     /  \       ==>             /  \         ==>       /  \  / \
		k2   B                     C    k1                A   C D   B
	   /  \                            /  \
	  C    D                          D    B 

 */
AVL* RL_Rotate(AVL* k3);


AVL* Insert(AVL* root, KEY_TYPE key);
AVL* Delete(AVL* root, KEY_TYPE key);
void InOrder(AVL* root);


#endif
