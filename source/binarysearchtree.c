//
//binary search tree operations
//

#include "..\header\binarysearchtree.h"
#include "..\header\stack.h"

//Search for a node the value of which is data, and return the pointer to this node
pNode Search(pNode root, int data)
{
	pNode sNode = NULL;
	pNode current = root;

	while (NULL != current)
	{
		if (data==current->data)
			sNode = current;
		else if (data < current->data)
			current = current->left;
		else 
			current = current->right;
	}
	
	return sNode;
}

//Insert to a binary search tree, and return the pointer to the root;
pNode Insert(pNode root, int data)
{
	pNode parent = NULL;
	pNode temp = root;
	pNode newNode = (pNode)malloc(sizeof(Node));

	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	
	if (NULL==root)
		return newNode;

	temp = root;
	while(NULL != temp)
	{
		parent = temp;
		if (data<temp->data)
			temp = temp->left;
		else
			temp = temp->right;
	}
	if (data < parent->data)
		parent->left = newNode;
	else
		parent->right = newNode;

	return root;
}

//Del a node with value data, returns true if succeeds and false if not found
pNode Delete(pNode root, int data)
{
	BOOL	bLeft;
	pNode	current;
	pNode	pre;	//predecessor
	pNode	par;	//parent node of predecessor
	pNode	par2;	//parent of the node to be deleted

	current = par2 = root;
	par = NULL;
	while(NULL != current)
	{
		if (data == current->data)
		{
			pre = current->left;
			if (NULL != pre)
			{
				//find predecessor
				while (NULL != pre->right)
				{
					par = pre;
					pre = pre->right;
				}
				if (par != NULL)
				{
					if (pre->left != NULL)
						par->right = pre->left;
					else
						par->right = NULL;
				}
				
				if (current->left != pre)
					pre->left = current->left;
				else
					pre->left = NULL;
				if (current->right != pre)
					pre->right = current->right;
				else 
					pre->right = NULL;
				if (par2!=current)
					if (bLeft)
						par2->left = pre;
					else
						par2->right = pre;
				if (current!=root)
					pre = root;
				free(current);
				return pre;
			}
			else		//delete the node directly
			{
				if (par2!=current)
					if (bLeft)
						par2->left = current->right;
					else
						par2->right = current->right;
				if (current != root)
					pre = root;
				free(current);
				return pre;
			}
		}
		else if (data < current->data)
		{
			par2 = current;
			current = current->left;
			bLeft = TRUE;
		}
		else
		{
			par2 = current;
			current = current->right;
			bLeft = FALSE;
		}
	}
	return root;
}	

//construct a binary search tree, and return the root;
pNode ConstructBST(int *data, int len)
{
	int i;
	pNode root = NULL;

	root = Insert(root, data[0]);
	for (i=1; i<len; i++)
	{
		Insert(root, data[i]);
	}
	return root;
}

//recursive implementation of traverse
//Inorder
void Intravese_re(pNode root)
{
	if (root->left!=NULL)
		Intravese_re(root->left);
	printf("%d	", root->data);
	if (root->right!=NULL)
		Intravese_re(root->right);
}
//preorder
void Pretraverse_re(pNode root)
{
	printf("%d	", root->data);
	if (root->left!=NULL)
		Pretraverse_re(root->left);
	if (root->right!=NULL)
		Pretraverse_re(root->right);
}
//postorder
void Posttraverse_re(pNode root)
{
	if (NULL != root->left)
		Posttraverse_re(root->left);
	if (NULL != root->right)
		Posttraverse_re(root->right);
	printf("%d	", root->data);
}

//nonrecursive implementation of traverse
//Inorder traversal without recursion or stack. Morris traversal
void MorrisIntraverse(pNode root)
{
	pNode current = root;
	pNode pre;		//predecessor

	while (NULL != current)
	{
		if (NULL == current->left)			//print root
		{
			printf("%d	", current->data);
			current = current->right;
		}
		else								//traverse left branch
		{
			pre = current->left;
			while(NULL != pre->right && pre->right != current)		//find the predecessor of current node
			{
				pre = pre->right;
			}
			if (NULL == pre->right)
			{
				pre->right = current;		//Insert subtree rooted at current node to the right branch of its predecessor
				current = current->left;	//move to the next level
			}
			else		//pre->right==current
			{
				printf("%d	", current->data);	//print root
				pre->right = NULL;			//restore the structure
				current = current->right;	//traverse right branch
			}
		}
	}
}

//preorder traversal without stack or recursion. Modfified morris traversal.
void MorrisPreTraverse(pNode root)
{
	pNode current = root;
	pNode pre;

	while(NULL != current)
	{
		if (NULL == current->left)
		{
			printf("%d	", current->data);			//print root
			current = current->right;		//move to right branch if left branch is null
		}
		else
		{
			pre = current->left;
			while(NULL != pre->right && pre->right != current)		//search for the predecessor of current node
			{
				pre = pre->right;
			}
			if (NULL == pre->right)
			{
				pre->right = current;		//insert substree rooted at current mode to the right branch of its predecessor pre
				printf("%d	", current->data);
				current = current->left;	//move to the left branch
			}
			else
			{
				pre->right = NULL;			//restore  structure
				current = current->right;	//move to the right branch
			}
		}
	}
}

//Inorder traversal with stack. 
void Intraverse(pNode root)
{
	Stack S;
	Node  poped;
	pNode temp = root;

	poped.left = poped.right = NULL;

	InitStack(&S);

	while (TRUE)
	{
		while(NULL != temp)
		{
			PushS(&S, *temp);
			temp = temp->left;
		}
		if(!PopS(&S, &poped))
			break;
		printf("%d	", poped.data);
		temp = poped.right;
	}
	DestroyStack(&S);
}

//Preorder traverse with stack
void Pretraverse(pNode root)
{
	pNode	current = root;
	Node	temp;
	Stack S;

	InitStack(&S);
	temp.left = temp.right = NULL;

	while(TRUE)
	{
		while(NULL != current)
		{
			printf("%d	", current->data);
			PushS(&S, *current);
			current = current->left;
		}
		if (!PopS(&S, &temp))
			break;
		current = temp.right;
	}
	DestroyStack(&S);
}

//Post order traversal with stack
void Posttraverse(pNode root)
{
	Node  poped;
	pNode current = root;
	Stack S;

	InitStack(&S);

	while(TRUE)
	{
		while(NULL != current)
		{
			PushS(&S, *current);
			current = current->left;
		}
		if (!PopS(&S, &poped))
			break;
		
		current = poped.right;
		if (poped.right!=NULL)
		{
			poped.right = NULL;
			PushS(&S, poped);			
		}
		else
		{
			printf("%d	", poped.data);
		}
	}

	DestroyStack(&S);
}