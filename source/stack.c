//
//stack operations
//
#include "..\header\stack.h"

void InitStack(Stack *S)
{
	ElemType *temp;
	
	temp = (ElemType *)malloc(sizeof(ElemType));

	S->stacksize = 1;
	S->base = S->top = temp;
}

void DestroyStack(Stack *S)
{
	if (S->base)
		free(S->base);
	S->top = NULL;
	S->stacksize = 0;
}

BOOL IsEmpty(Stack *S)
{
	if (S->base == S->top)
		return TRUE;
	return FALSE;
}

BOOL PushS(Stack *S, ElemType data)
{
	if (S->top-S->base >= (S->stacksize))		//increase stack size
	{
		S->stacksize++;
		S->base = (ElemType *)realloc(S->base, sizeof(ElemType)*S->stacksize);
		S->top = S->base+S->stacksize-1;		//we should update the adrress for S->top since the address of S->base might have been changed by realloc function
	}
	*S->top++ = data;
	return TRUE;
}

BOOL PopS(Stack *S, ElemType *data)
{
	if (IsEmpty(S))
		return FALSE;
	--S->top;
	*data = *S->top;
	return TRUE;
}
