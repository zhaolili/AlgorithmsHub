#ifndef _STACK_H_
#define _STACK_H_

#include "..\header\common_def.h"
#include "binarysearchtree.h"

#define ElemType Node

typedef struct stack{
	ElemType	*base;
	ElemType	*top;
	int			stacksize;	//the size of the stack, not the number of elements
}Stack;

void InitStack(Stack *S);
void DestroyStack(Stack *S);
BOOL IsEmpty(Stack *S);
BOOL PushS(Stack *S, ElemType data);
BOOL PopS(Stack *S, ElemType *data);
#endif