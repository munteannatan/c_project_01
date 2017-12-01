#include <stdlib.h>
#include "cctree.h"

CC_TREE * rotate_left(CC_TREE *A, CC_TREE *B) {
	A->right = B->left;
	if (A->right != NULL) {
		A->right->parent = A;
	}
	B->left = A;
	A->parent = B;
	if (0 == B->Balance) {
		A->Balance = 1;
		B->Balance = -1;
	}
	else {
		A->Balance = 0;
		B->Balance = 0;
	}
	return B;
}

CC_TREE * rotate_right(CC_TREE *B, CC_TREE *A) {
	B->left = A->right;
	if (B->left != NULL) {
		B->left->parent = B;
	}
	A->right = B;
	B->parent = A;
	if (0 == A->Balance) {
		A->Balance = +1;
		B->Balance = -1;
	}
	else {
		A->Balance = 0;
		B->Balance = 0;
	}
	return A;
}
CC_TREE * RightLeft(CC_TREE *A, CC_TREE *B) {
	CC_TREE *C;
	C = B->left;
	B->left = C->right;
	if (NULL != B->left) {
		B->left->parent = B;
	}
	C->right = B;
	B->parent = C;
	A->right = C->left;
	if (NULL != A->right) {
		A->right->parent = A;
	}
	C->left = A;
	A->parent = C;
	if (C->Balance > 0) {
		B->Balance = 0;
		A->Balance = -1;
	}
	else if (0 == C->Balance) {
		B->Balance = 0;
		A->Balance = 0;
	}
	else {
			B->Balance = +1;
			A->Balance = 0;
	}
	C->Balance = 0;
	return C;
}

CC_TREE * LeftRight(CC_TREE *B, CC_TREE *A) {
	CC_TREE *C = A->right;
	A->right = C->left;
	if (NULL != A->right) {
		A->right->parent = A;
	}
	C->left = A;
	A->parent = C;
	B->left = C->right;
	if (NULL != B->left) {
		B->left->parent = B;
	}
	C->right = B;
	B->parent = C;
	if (C->Balance < 0) {
		A->Balance = 0;
		B->Balance = +1;
	}
	else if (0 == C->Balance)
	{
		A->Balance = 0;
		B->Balance = 0;
	}
	else
	{
		A->Balance = -1;
		B->Balance = 0;
	}
	C->Balance = 0;
	return C;
}

int Search(CC_TREE **Tree, int Value) {
	while ((*Tree)->Value != Value && (*Tree)->Height > 0)
	{
		if ((*Tree)->Value > Value) {
			(*Tree) = (*Tree)->left;
			continue;
		}
		(*Tree) = (*Tree)->right;
	}
	if ((*Tree)->Value == Value)
	{
		return 0;
	}
	if ((*Tree)->Value < Value)
	{
		return 1;
	}
	return -1;
}

int TreeInsert(CC_TREE *Tree, int Value) {
	if (0 == Tree->Multiplication) {
		Tree->Value = Value;
		Tree->Multiplication = 1;
		Tree->Balance = 0;
		return 0;
	}
	CC_TREE *Clone = Tree;
	int k = Search(&Clone, Value);
	if (0 == k)
	{
		(Clone->Multiplication)++;
		return 0;
	}
	CC_TREE* Son,*Father,*Result=NULL;
	if (k < 0) {
		Clone->left = (CC_TREE*)malloc(sizeof(Tree));
		Clone->left->parent = Clone;
		Clone->left->Value = Value;
		Clone->left->left = NULL;
		Clone->left->right = NULL;
		Clone->left->Balance = 0;
		Clone->left->Height = 0;
		Clone->left->Multiplication = 1;
		Son = Clone->left;
	}
	else
	{
		Clone->right = (CC_TREE*)malloc(sizeof(Tree));
		Clone->right->parent = Clone;
		Clone->right->Value = Value;
		Clone->right->left = NULL;
		Clone->right->right = NULL;
		Clone->right->Balance = 0;
		Clone->right->Height = 0;
		Clone->right->Multiplication = 1;
		Son = Clone->right;
	}
	for (Clone = Son->parent; Clone != NULL; Clone = Son->parent)
	{
		if (Son == Clone->right) {
			if (Clone->Balance > 0) {
				Father = Clone->parent;
				if (Son->Balance < 0) {
					Result = RightLeft(Clone, Son);
				}
				else
				{
					rotate_left(Clone, Son);
				}
			}
			else {
				if (Clone->Balance < 0) {
					Clone->Balance = 0;
					break;
				}
				Clone->Balance = 1;
				Son = Clone;
				continue;
			}
		}
		else {
			if (Clone->Balance < 0) {
				Father = Clone->parent;
				if (Son->Balance > 0) {
					Result = LeftRight(Clone, Son);
				}
				else {
					Result = rotate_right(Clone, Son);
				}
			}
			else {
				if (Clone->Balance > 0) {
					Clone->Balance = 0;
					break;
				}
				Clone->Balance = -1;
				Son = Clone;
				continue;
			}
		}
		if (NULL != Result) {
			Result->parent = Father;
		}
		if (Father != NULL) {
			if (Clone == Father->left) {
				Father->left = Result;
			}
			else {
				Father->right = Result;
			}
		}
		else {
			CC_TREE *Aux = (CC_TREE*)malloc(sizeof(CC_TREE));

			Aux->Balance = Tree->Balance;
			Tree->Balance = Result->Balance;
			Result->Balance = Aux->Balance;

			Aux->Multiplication = Tree->Multiplication;
			Tree->Multiplication = Result->Multiplication;
			Result->Multiplication = Aux->Multiplication;

			Aux->Height = Tree->Height;
			Tree->Height = Result->Height;
			Result->Height = Aux->Height;

			Aux->left = Tree->left;
			Tree->left = Result->left;
			Result->left = Aux->left;

			Aux->right = Tree->right;
			Tree->right = Result->right;
			Result->right = Aux->right;

			Aux->parent = Tree->parent;
			Tree->parent = Result->parent;
			Result->parent = Aux->parent;

			free(Aux);
			break;
		}

	}
	return 0;
}

int TreeCreate(CC_TREE **Tree) {
	*Tree = (CC_TREE*)malloc(sizeof(CC_TREE));
	(*Tree)->Height = 0;
	(*Tree)->Multiplication = 0;
	(*Tree)->left = NULL;
	(*Tree)->right = NULL;
	(*Tree)->parent = NULL;
	return 0;
}

int TreeContains(CC_TREE *Tree, int Value) {
	while (Tree->Value != Value&&Tree->Height > 0)
	{
		if (Tree->Value > Value) {
			Tree = Tree->left;
			continue;
		}
		Tree = Tree->right;
	}
	if (Tree->Value == Value)
	{
		return 1;
	}
	return 0;
}
int TreeGetHeight(CC_TREE *Tree) {
	return Tree->Height;
}
int TreeClear(CC_TREE *Tree) {
	if (NULL != Tree->left) {
		TreeClear(Tree->left);
	}
	if (NULL != Tree->right) {
		TreeClear(Tree->right);
	}
	free(Tree);
	return 0;
}

int TreeDestroy(CC_TREE **Tree) {
	TreeClear(*Tree);
	free(Tree);
	return 0;
}
int TreeGetCount(CC_TREE *Tree) {
	if (NULL == Tree) {
		return 0;
	}
	return 1 + TreeGetCount(Tree->left) + TreeGetCount(Tree->right);
}