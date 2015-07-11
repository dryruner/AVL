//AVL 

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

/* DD(Y rota a la derecha):

        k2                   k1
       /  \                 /  \
      k1   Z     ==>       X   k2
     / \                      /  \
    X   Y                    Y    Z
 */

/*
 Retornar a donde deberia apuntar el nodo raiz
 */
AVL* AVLTree::RR_Rotate(AVL* k2) {
    AVL* k1 = k2->lchild;
    k2->lchild = k1->rchild;
    k1->rchild = k2;
    k2->height = max(getHeight(k2->lchild), getHeight(k2->rchild)) + 1;
    k1->height = max(getHeight(k1->lchild), k2->height) + 1;
    return k1;
}

/* II(Y rota a la izquierda):

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



/* ID(B rota a la izquierda, C rota a la derecha):
      k3                         k3                       k2
     /  \                       /  \                     /  \
    k1   D                     k2   D                   k1   k3
   /  \         ==>           /  \        ==>          / \   / \
  A    k2                    k1   C                   A  B  C   D
      /  \                  /  \
     B    C                A    B
 */

/*
Retornar a donde deberia apuntar el nodo raiz
 */
AVL* AVLTree::LR_Rotate(AVL* k3) {
    k3->lchild = LL_Rotate(k3->lchild);
    return RR_Rotate(k3);
}

/* DI(D rota a la derecha, entonces C rota a la izquierda):

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

/* 
 * Retornar a donde deberia apuntar el nodo raiz. El nodo raiz cambia frecuentemente en
 * insercion y eliminacion, asi que el nodo raiz deberia apuntar al nodo raiz REAL.
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


/* 
 * Retornar a donde deberia apuntar el nodo raiz. El nodo raiz cambia frecuentemente en
 * insercion y eliminacion, asi que el nodo raiz deberia apuntar al nodo raiz REAL.
 */
AVL* AVLTree::Delete(AVL* root, KEY_TYPE key) {
    if (!root)
        return NULL;
    if (key == root->key) {
        if (root->lchild == NULL && root->rchild == NULL) {
            /* 
             si el elemento es hoja, entonces lo eliminamos y retornamos el valor. Cuando
             el nodo que se elimina es interno, entonces se retorna el valor que será sustituido
             */
            AVL* temp = root;
            root = NULL;
            delete(temp);
            return root;
            
        } else if (root->lchild != NULL) {
            /* 
             En este caso retornamos un sustituto del nodo que queremos eliminar 
             con el elemento mayor de su subarbol izquierdo
             */
            AVL* temp = root->lchild;
            while (temp->rchild)
                temp = temp->rchild;
            /* reemplazar el valor */
            root->key = temp->key;
            /* Eliminar el nodo (sucesor) que en realidad deberia ser eliminado */
            root->lchild = Delete(root->lchild, temp->key);

        } else if (root->rchild != NULL) {
            /* Si no hay un subarbol izquierdo, entonces obtenemos el elemento mas pequeño del subarbol derecho */
            AVL* temp = root->rchild;
            while (temp->lchild)
                temp = temp->lchild;
            /* reemplazar el valor */
            root->key = temp->key;
            /* Eliminar el nodo (sucesor) que en realidad deberia ser eliminado */
            root->rchild = Delete(root->rchild, temp->key);
        }

    } else if (key < root->key)
        root->lchild = Delete(root->lchild, key);
    else
        root->rchild = Delete(root->rchild, key);
    
    /* 
     Obtenemos la nueva altura y rotamos el arbol si es necesario. Notese que esta parte
     de codigo se invoca en cada paso recursivo
     */
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
/* Inicializar el AVL para el menu */
void AVLTree::AVLmenu(){
        AVL* root = NULL;
	int vector[] = {15,6,18,3,7,17,20,2,4,13,9};
	const int length = sizeof(vector)/sizeof(int);
	for(int i = 0; i< length;i++)
		root = AVLTree::Insert(root, vector[i]);
        AVLmenu(root);
}


void AVLTree::AVLmenu(AVL* root){
    using namespace std;
    int choice, item;
    while (1)
    {
        //if (system("CLS")) system("clear");
        cout << endl;
        cout<<"---------------------"<<endl;
        cout<<"Arbol AVL"<<endl;
        cout<<"---------------------"<<endl;
        cout<<"\t1.Insertar elemento"<<endl;
        cout<<"\t2.Desplegar arbol AVL"<<endl;
        cout<<"\t3.EnOrden"<<endl;
        cout<<"\t4.PreOrden"<<endl;
        cout<<"\t5.PostOrden"<<endl;
        cout<<"\t6.Eliminar elemento"<<endl;
        cout<<"\t7.Salir"<<endl;
        cout<<"\tIngrese su opcion: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Ingrese el valor deseado : ";
            cin>>item;
            root = AVLTree::Insert(root, item);
            break;
        case 2:
            if (root == NULL)
            {
                cout<<"Arbol esta vacio"<<endl;
                continue;
            }
            cout<<"Arbol AVL:"<<endl;
            AVLTree::Display(root, 0);
            break;
        case 3:
            cout<<"EnOrden:"<<endl;
            AVLTree::InOrder(root);
            cout<<endl;
            break;
        case 4:
            cout<<"PreOrden:"<<endl;
            AVLTree::PreOrder(root);
            cout<<endl;
            break;
        case 5:
            cout<<"PostOrden:"<<endl;
            AVLTree::PostOrder(root);    
            cout<<endl;
            break;
        case 6:
            cout<<"Ingrese el valor a eliminar: ";
            cin>>item;
            root = AVLTree::Delete(root, item);
            break;
        case 7:
            return;    
            break;
        default:
            cout<<"Opcion Invalida"<<endl;
        }
    }
}
