#ifndef _BST_H_
#define _BST_H_

#include "common_def.h"

typedef struct node{
	int		data;
	struct node	*left;
	struct node *right;
}Node, *pNode;

pNode Search(pNode root, int data);
pNode Insert(pNode root, int data);
pNode ConstructBST(int *data, int len);
void Intravese_re(pNode root);
void Pretraverse_re(pNode root);
void Posttraverse_re(pNode root);
void MorrisIntraverse(pNode root);
void MorrisPreTraverse(pNode root);
void MorrisPostTraverse(pNode root);
void Intraverse(pNode root);
void Pretraverse(pNode root);
void Posttraverse(pNode root);
pNode Delete(pNode root, int data);

#endif