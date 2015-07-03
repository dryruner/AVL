#include <stdlib.h>
#include<stdio.h>
#include<iostream>
#include "AVL.h"
using namespace std;


int main(int argc, char* argv[])
{
	AVL* root = NULL;
	int vector[] = {15,6,18,3,7,17,20,2,4,13,9};
	const int length = sizeof(vector)/sizeof(int);
	for(int i = 0; i< length;i++)
		root = AVLTree::Insert(root, vector[i]);
	AVLTree::AVLmenu(root);
	printf("\n");
	return 0;
}
