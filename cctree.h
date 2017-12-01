#pragma once
typedef struct _CC_TREE {
	int Height, Value;
	int Balance;
	int Multiplication;
	struct _CC_TREE *right, *left, *parent;
} CC_TREE;
int TreeCreate(CC_TREE **Tree);
int TreeDestroy(CC_TREE **Tree);
int TreeInsert(CC_TREE *Tree, int Value);
int TreeRemove(CC_TREE *Tree, int Value);
int TreeContains(CC_TREE *Tree, int Value);
int TreeGetCount(CC_TREE *Tree);
int TreeGetHeight(CC_TREE *Tree);
int TreeClear(CC_TREE *Tree);
int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value);
int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value);
int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value);