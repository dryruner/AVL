#ifndef __AVL_H__
#define __AVL_H__

typedef int KEY_TYPE;

/* No hay punter padre */
typedef struct AVL{
	KEY_TYPE key;
	int height;
	struct AVL* lchild;
	struct AVL* rchild;
}AVL;

class AVLTree{
private:
    static void AVLmenu(AVL* root);
public:
    static void AVLmenu();
	static AVL* New_Node(KEY_TYPE key, AVL* lchild, AVL* rchild, int height = 0);
	static inline int getHeight(AVL* node);
	static inline int max(int a, int b);
	/*
	Retornar a donde deberia apuntar el nodo raiz
	 */
	static AVL* RR_Rotate(AVL* k2);
	static AVL* LL_Rotate(AVL* k2);
	/*
	Retornar a donde deberia apuntar el nodo raiz
	 */
	static AVL* LR_Rotate(AVL* k3);

	/* DI(D rota a la derecha, C rota a la izquierda):*/
	static AVL* RL_Rotate(AVL* k3);


	static AVL* Insert(AVL* root, KEY_TYPE key);
	static AVL* Delete(AVL* root, KEY_TYPE key);
	static void InOrder(AVL* root);
	static void PreOrder(AVL* root);
	static void PostOrder(AVL* root);
	static void Display(AVL*, int);
};
#endif
