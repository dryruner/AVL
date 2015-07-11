#include "RedBlack.h"
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <stdlib.h>

/* Retorna un puntero al nodo que es abuelo de n */
node* RedBlack::Grandparent(node* n){
    if(n->parent != NULL)
        return n->parent->parent;
    else 
        return NULL;
}

/* Retorna un puntero al hermano de n. Si no tiene, retorna NULL */
node* RedBlack::Sibling(node* n){
    node* parent = n->parent;
    if(parent == NULL) return NULL;
    
    if(parent->left == n)
        return parent->right;
    
    else if(parent->right == n)
        return parent->left;
}

/* Retorna un puntero al tio de n. Si no tiene, retorna NULL */
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
 * Este metodo ayuda en la rotacion de nodos. Reemplaza el nodo viejo 'oldno'
 * con el nuevo nodo 'newno'
 */
void RedBlack::replace_node(node* oldno, node* newno){
    //si oldno es raiz    
    if (oldno->parent == NULL)
    {
        this->root = newno;
    }
    else
    {   
        /* si oldno es un hijo izquierdo, entonces newno sera setteado como el hijo izquierdo
         del padre de oldno, o derecho en caso de que oldno fuese hijo derecho */
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

/*  Rotacion a la derecha
        k2                   k1
       /  \                 /  \
      k1   Z     ==>       X   k2
     / \                      /  \
    X   Y                    Y    Z
  
 Cambia la estructura
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


/* Rotacion a la izquierda
        k2                       k1
       /  \                     /  \
      X    k1         ==>      k2   Z
          /  \                /  \
         Y    Z              X    Y
 Cambia la estructura
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

// Si es NULL es hoja, asi que el color va a ser negro
color RedBlack::node_color(node* n){
    return n == NULL ? BLACK : n->color;
}

/*
 * Verifica las propiedades[reglas], ver .h para ver todas
 */
void RedBlack::verify_properties(){
    verify_property_1(this->root);
    verify_property_2();
    //property 3 no se verifica ya que declara que todas las hojas son negras
    verify_property_4(this->root);
    verify_property_5(this->root);
}

/*
 * Propiedad 1: Un nodo es rojo o negro
 */
void RedBlack::verify_property_1(node* root){
    assert (node_color(root) == RED || node_color(root) == BLACK);
    if (root == NULL)
        return;
    verify_property_1(root->left);
    verify_property_1(root->right);
}

/*
 * Propiedad 2: La raiz es negra
 */
void RedBlack::verify_property_2(){
    assert (node_color(this->root) == BLACK);
}

/*
 * Propiedad 3: Todo nodo rojo debe tener dos nodos hijos negros, y por ende, un padre negro
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
 * Propiedad 5: Todo camino de un nodo dado a cualquiera de sus descendientes nodo-NULL
 * contiene la misma cantidad de nodos negros
 */
void RedBlack::verify_property_5(node* root){
    int black_count_path = -1;
    verify_property_5_rec(root, 0, &black_count_path);
}

/*
 * Una funcion auxiliar que hace la verificacion de la propiedad 5. Es un metodo recursivo, todas sus 'instancias'
 * comparten el mismo valor 'path_black_count' ya que es un puntero
 * Parametros:
 * node* n: Nodo que testeamos en una invocacion recursiva
 * int black_count: Nodos negros en un camino dado
 * int* path_black_count: Es un puntero que especifica el valor de 'black_count' que todo camino deberia tener.
 *                        Es un valor inicial -1 y la primera funcion recursiva establece su valor.
 */
void RedBlack::verify_property_5_rec(node* n, int black_count, int* path_black_count){
    if (node_color(n) == BLACK)
    {
        //si n es negro, +1 al contador negro del camino
        black_count++;
    }
    //si n es NULL (= una hoja)
    if (n == NULL)
    {
        /* si 'path_black_count* tiene un valor -1 = no hay ningun otro camino recursivo
         que haya terminado su ejecucion y que el camino recursivo actual es el primero en llegar a este punto */
        if (*path_black_count == -1)
        {
            //ya que nuestro contador negro es el mismo que cualquier otro camino recursivo que queremos y setteamos
            *path_black_count = black_count;
        }
        /* si path_black_count no es -1, quiere decir que otro camino recursivo ya especifico el path_black count.
         Si el contador es diferente, quiere decir que no todos los caminos tienen el mismo numero de nodos negros*/
        else if(black_count != *path_black_count)
        {
            /* esto siempre detendra el programa, ya que el unico modo en que esta parte sera ejectuada es si 'black_count != *path_black_count' */
            assert (black_count == *path_black_count);
        }
        return;
    }
    
    verify_property_5_rec(n->left,  black_count, path_black_count);
    verify_property_5_rec(n->right, black_count, path_black_count);
}


/* 
 * Insercion es igual que en un arbol binario. Es un metodo iterativo. Al final llama
 * a 'insert_case1()9, que ejecutara una cadena de funciones que arreglaran errores creados
 * por la insercion. Despues llamara 'verify_cases()', que chequea que ninguna propiedad el arbol haya sido 
 * rota
 */
void RedBlack::Insert(int _key){
    
    rbtree_node* node_insert = new rbtree_node();
    //nuevos nodos siempre son insertados como rojos
    node_insert->color = RED;
    node_insert->key = _key;
    if (this->root == NULL)
    {
        this->root = node_insert;
    }
    else
    {
        node* n = this->root;
        
        //insert iterativo
        while (1)
        {
            /* si el nodo ya existe entonces lo retornamos, ya que no pueden haber valores repetidos en el arbol*/
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
 * Verifica si n es raiz. Si lo es, entonces se convertira en negro. Si no, entonces continua con el 'insert_case2()'
 */
void RedBlack::insert_case1(node* n){
    if (n->parent == NULL)
        n->color = BLACK;
    else
        insert_case2(n);
}

/*
 * Sabemos que n es rojo, si su padre es negro entonces todo esta bien y no tiene sentido continuar
 * chequeando que las reglas esten bien. Si el padre NO es negro, entonces seguimos con 'insert_case3()'
 */
void RedBlack::insert_case2(node* n){
    if (node_color(n->parent) == BLACK)
        return;
    else
        insert_case3(n);
}

/*
 * Ya sabemos que el padre de n no es NULL o negro, entonces chequeamos si el tio es rojo. Si lo es,
 * el tio y el padre seran negros y el abuelo rojo. En este punto sabemos que del abuelo de n a n toda propiedad
 * es consistente, pero no sabemos si cambiando el color del abuelo causo probelmas, por lo que empezamos la cadena de 
 * checks de reglas otra vez, pero sin chequear el abuelo de n.
 * Si el tio de n no es rojo, seguimos con 'insert_case4()'
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
 * En este punto sabemos que
 * n es rojo
 * padre de n no es NULL
 * padre de n es rojo
 * tio de n es negro
 * Entonces necesitamos rotar el arbol para hacer las propiedades consistentes. Esta rotacion
 * consiste en rotar el padre de n y el abuelo de n una vez. En 'insert_case4()' el padre de n es
 * rotado y entonces n apunta al padre y seguimos con 'insert_case5()'
 */
void RedBlack::insert_case4(node* n){
    //si n es hijo derecho y el padre es izquierdo, rotamos a izquierda
    //       Gp(B)                     Gp(B)
    //      /                          /
    //  Pa(R)           ==>         n(R)
    //      \                       /
    //      n(R)                 Pa(R)
    if (n == n->parent->right && n->parent == Grandparent(n)->left)
    {
        Left_Rotate(n->parent);
        n = n->left; //apuntar al padre
    }
    
    //si n es izquierdo y el padre de n es un hijo derecho, rotamos a la derecha
    //       Gp(B)                     Gp(B)
    //            \                        \
    //            Pa(R)           ==>       n(R)
    //            /                             \
    //         n(R)                             Pa(R)
    else if (n == n->parent->left && n->parent == Grandparent(n)->right)
    {
        Right_Rotate(n->parent);
        n = n->right; //apuntar al padre
    }
    insert_case5(n);
}

/*
 * Este metodo hace la segunda rotacion, pero esta vez rota el abuelo de n. 
 * Antes de rotar el padre de n se pone negro y el del abuelo de n de rojo.
 */
void RedBlack::insert_case5(node* n){
    n->parent->color = BLACK;
    Grandparent(n)->color = RED;
    
    //si n es un hijo izquierdo y el padre es un hijo izquierdo, rotar a la derecha
    //       Gp(R)                
    //      /                       Pa(B)  
    //    Pa(B)           ==>      /    \
    //    /                      n(R)   Gp(R)
    //  n(R)                    
    if (n == n->parent->left && n->parent == Grandparent(n)->left)
    {
        Right_Rotate(Grandparent(n));
    }
        
    //si n es un hijo derecho y el padre es un hijo derecho, rotar a la izquierda
    //       Gp(R)                
    //           \                        Pa(B)  
    //          Pa(B)         ==>        /    \
    //             \                   n(R)   Gp(R)
    //             n(R)              
    else
    {
        //unico caso posible, por eso assert en vez de un if
        assert (n == n->parent->right && n->parent == Grandparent(n)->right);
        Left_Rotate(Grandparent(n));
    }
}

/*
 * Desplegar el arbol
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

/* Devuelve un puntero al nodo que tenga como valor _key */
node* RedBlack::lookup_node(int _key){
    node* n = this->root;
    while (n != NULL)
    {
        if (_key == n->key)
        {
            return n;
        }
        else if (_key < n->key)
        {
            n = n->left;
        }
        else
        {
            assert(_key > n->key);
            n = n->right;
        }
    }
    return n;
}

/* Metodo que se encarga de empezar el proceso de eliminacion */
void RedBlack::Delete(int _key){
    node* n = lookup_node(_key); //puntero al nodo que se quiere eliminar
    node* child;
    if (n == NULL)
        //si no existe ..
        return; 
    
    if (n->left != NULL && n->right != NULL)
    {
        //si el nodo a eliminar NO es un nodo hoja
        
        //se obtiene el nodo con el mayor valor de subarbol izquierdo
        node* pred = n->left;
        while(pred->right != NULL)
            pred = pred->right;
        
        //se sustituye el valor del nodo a eliminar con el mayor valor 
        //del subarbol izquierdo
        n->key   = pred->key; 
        
        //como ya podemos decir que 'eliminamos' el nodo ahora lo que nos
        //interesa es deshacernos del nodo de mayor valor del subarbol izquierdo
        n = pred;
    }
    assert(n->left == NULL || n->right == NULL); //solo para estar seguros de q n tiene al menos un hijo que sea NULL
    
    //'child' es apunta al unico hijo que n tenga
    child = n->right == NULL ? n->left  : n->right; 
    
    
    if (node_color(n) == BLACK)
    {
        n->color = node_color(child); 
        delete_case1(n); //empezamos los pasos para eliminar el nodo
    }
    replace_node(n, child);
    free(n); //liberamos el espacio de memoria
    verify_properties(); //verificamos que todo este en orden
}

/* Si n es raiz entonces no hay nada que hacer y terminamos */
void RedBlack::delete_case1(node* n){
    if (n->parent == NULL)
        return;
    else
        delete_case2(n); //pasamos al caso 2
}

/* Si el color del hermano de n es rojo entonces le cambiamos el color al padre de n para que sea Rojo y al 
 * hermano le cambiamos el color para que sea Negro. Si n es hijo izquierdo entonces rotamos el padre
 * de n a la izquierda, si es hijo derecho entonces rotamos el padre de n a la derecha */
void RedBlack::delete_case2(node* n){
    if (node_color(Sibling(n)) == RED) //si el hermano de n es ROJO
    {
        n->parent->color = RED;
        Sibling(n)->color = BLACK;
        if (n == n->parent->left)
            Left_Rotate(n->parent);
        else
            Right_Rotate(n->parent);
    }
    delete_case3(n);// seguimos con el caso 3
}

/* Si el padre de n, el hermano de n, los hijos (izquierdo y derecho) del hermano de n son NEGROS entonces
 * le cambiamos el color al hermano de n para que sea ROJO y volvemos a empezar con los casos de eliminacion
 * pero esta ves pasamos al padre de n como parametro para el caso 1. Si este no fuera el caso entonces 
 * proseguimos con el caso 4 */
void RedBlack::delete_case3(node* n){
    if (node_color(n->parent) == BLACK && node_color(Sibling(n)) == BLACK &&
        node_color(Sibling(n)->left) == BLACK && node_color(Sibling(n)->right) == BLACK)
    {
        Sibling(n)->color = RED;
        delete_case1(n->parent);
    }
    else
        delete_case4(n);
}

/* Si el padre de n, el hermano de n, los hijos (izquierdo y derecho) del hermano de n son ROJOS entonces
 * le cambiamos el color al hermano de n para que sea ROJO y al padre de n para que sea NEGRO.
 * Si este no fuera el caso entonces  proseguimos con el caso 5 */
void RedBlack::delete_case4(node* n){
    if (node_color(n->parent) == RED && node_color(Sibling(n)) == BLACK &&
        node_color(Sibling(n)->left) == BLACK && node_color(Sibling(n)->right) == BLACK)
    {
        Sibling(n)->color = RED;
        n->parent->color = BLACK;
    }
    else
        delete_case5(n);
}

/* Si n es hijo izquierdo y  el color del hermano de n y del hijo derecho del hermano de n es NEGRO
 * y el hijo izquierdo del hermano de n es de color ROJO entonces le cambiamos el color al hermano de n
 * para que de ROJO y le cambiamos el color del hijo izquierdo de n a NEGRO y rotamos el hermano de n
 * hacia la derecha.
 * Si fuera el caso de que n es hijo derecho y el color del hermano de n y el color del hijo izquierdo del hermano
 * de n es NEGRO y el color del hijo derecho del hermano de n es ROJO entonces le cambiamos el color al 
 * hermano de n para que sea ROJO, al hijo derecho del hermano de n para que sea NEGRO y rotamos
 * el hermano de n hacia la derecha.
 * Luego proseguimos con el caso 6 */
void RedBlack::delete_case5(node* n){
    if (n == n->parent->left && node_color(Sibling(n)) == BLACK &&
        node_color(Sibling(n)->left) == RED && node_color(Sibling(n)->right) == BLACK)
    {
        Sibling(n)->color = RED;
        Sibling(n)->left->color = BLACK;
        Right_Rotate(Sibling(n));
    }
    else if (n == n->parent->right && node_color(Sibling(n)) == BLACK &&
             node_color(Sibling(n)->right) == RED && node_color(Sibling(n)->left) == BLACK)
    {
        Sibling(n)->color = RED;
        Sibling(n)->right->color = BLACK;
        Left_Rotate(Sibling(n));
    }
    delete_case6(n);
}

/* Realizamos el caso 6 */
void RedBlack::delete_case6(node* n){
    //le cambiamos el color al hermano de n para que sea del mismo color que el padre de n
    Sibling(n)->color = node_color(n->parent);
    
    //al padre de n le ponemos color negro
    n->parent->color = BLACK;
    
    //si n es hijo izquierdo
    if (n == n->parent->left)
    {
        assert (node_color(Sibling(n)->right) == RED); //nos aseguramos que el color del hijo derecho del hermano de n sea ROJO
        Sibling(n)->right->color = BLACK; //le ponemos al hijo derecho del hermano de n el color NEGRO
        Left_Rotate(n->parent); // rotamos el padre de n a la izquierda 
    }
    else
    {
        assert (node_color(Sibling(n)->left) == RED); //nos aseguramos que el color del hijo izquierdo del hermano de n sea ROJO
        Sibling(n)->left->color = BLACK;//le ponemos al hijo izquierdo del hermano de n el color NEGRO
        Right_Rotate(n->parent);// rotamos el padre de n a la derecha 
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
        cout<<"Arbol Rojo-Negro"<<endl;
        cout<<"---------------------"<<endl;
        cout<<"\t1.Insertar elemento"<<endl;
        cout<<"\t2.Desplegar Arbol"<<endl;
        cout<<"\t3.Eliminar Elemento"<<endl;
        cout<<"\t4.Salir"<<endl;
        cout<<"\tIngrese su opcion: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Ingrese el valor deseado: ";
            cin>>item;
            tree->RedBlack::Insert(item);
            break;
        case 2:
            if (tree->root == NULL)
            {
                cout<<"Arbol vacio"<<endl;
                continue;
            }
            cout<<"Arbol Rojo-Negro:"<<endl;
            tree->RedBlack::Display(tree->root,0);
            break;
        case 3:
            cout<<"Ingrese el elemento a eliminar: ";
            cin>>item;
            tree->Delete(item);
            break;
        case 4:
            return;    
            break;
        default:
            cout<<"Opcion Invalida"<<endl;
        }
    }
}