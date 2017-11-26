typedef struct _CC_VECTOR {
    int dim;
    int *vect;
} CC_VECTOR;
int VecCreate(CC_VECTOR **Vector);
int VecDestroy(CC_VECTOR **Vector);
int VecInsertTail(CC_VECTOR *List, int Value);
int VecInsertHead(CC_VECTOR *List, int Value);
int VecInsertAfterIndex(CC_VECTOR *List, int Index, int Value);
int VecRemoveByIndex(CC_VECTOR *List, int Index);
int VecGetValueByIndex(CC_VECTOR *List, int Index, int *Value);
int VecGetCount(CC_VECTOR *List);
int VecClear(CC_VECTOR *List);
int VecSort(CC_VECTOR *List);
