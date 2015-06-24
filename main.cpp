#include <cstdlib>
#include<stdio.h>
#include<iostream>
#include "AVL.h"
using namespace std;

int main(int argc, char* argv[])
{
	AVL* root = NULL;
	int vector[] = {15,6,18,3,7,17,20,2,4,13,9};
//	int vector[] = {15};
	const int length = sizeof(vector)/sizeof(int);
	for(int i = 0; i< length;i++)
		root = Insert(root, vector[i]);
	
        Display(root, root->height);
	int input;
	printf("\nplease input the value you want to delete: ");
	scanf("%d",&input);
	
	while(1)
	{
		root = Delete(root, input);
		printf("\nAfter delete %u:\n",input);
		Display(root, root->height);
		printf("\nplease input another value you want to delete: ");
		scanf("%u",&input);
	}
	printf("\n");
	return 0;
}