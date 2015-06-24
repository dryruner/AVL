#include <stdlib.h>
#include<stdio.h>
#include<iostream>
#include "AVL.h"
using namespace std;

void menu(AVL* root){
    int choice, item;
    while (1)
    {
        //if (system("CLS")) system("clear");
        cout << endl;
        cout<<"---------------------"<<endl;
        cout<<"AVL Tree Implementation"<<endl;
        cout<<"---------------------"<<endl;
        cout<<"1.Insert Element into the tree"<<endl;
        cout<<"2.Display AVL Tree"<<endl;
        cout<<"3.InOrder"<<endl;
        cout<<"4.PreOrder"<<endl;
        cout<<"5.PostOrder"<<endl;
        cout<<"6.Delete Item from tree"<<endl;
        cout<<"7.Exit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter value to be inserted: ";
            cin>>item;
            root = Insert(root, item);
            break;
        case 2:
            if (root == NULL)
            {
                cout<<"Tree is Empty"<<endl;
                continue;
            }
            cout<<"AVL Tree:"<<endl;
            Display(root, 0);
            break;
        case 3:
            cout<<"InOrder:"<<endl;
            InOrder(root);
            cout<<endl;
            break;
        case 4:
            cout<<"PreOrder:"<<endl;
            PreOrder(root);
            cout<<endl;
            break;
        case 5:
            cout<<"PostOrder:"<<endl;
            PostOrder(root);    
            cout<<endl;
            break;
        case 6:
            cout<<"Enter the value to be deleted: ";
            cin>>item;
            root = Delete(root, item);
            break;
        case 7:
            exit(1);    
            break;
        default:
            cout<<"Invalid Option"<<endl;
        }
    }
}

int main(int argc, char* argv[])
{
	AVL* root = NULL;
	int vector[] = {15,6,18,3,7,17,20,2,4,13,9};
	const int length = sizeof(vector)/sizeof(int);
	for(int i = 0; i< length;i++)
		root = Insert(root, vector[i]);
	menu(root);
	printf("\n");
	return 0;
}