#include <stdio.h>
#include <stdlib.h>
#include 'ccheap.h'
#include 'ccvector'

int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements){
    *MaxHeap=(CC_HEAP*)malloc(sizeof(CC_HEAP));
    (*MaxHeap)->dim=VecGetCount(InitialElements);
    VecCreate(&(*MaxHeap)->vect);
    int i;
    for(i=0;i<(*MaxHeap)->dim;i++){
        int value;
        VecGetValueByIndex(InitialElements,i,value);
        VecInsertTail((*MaxHeap)->vect,value);
    }
    for(i=(*MaxHeap)->dim>>1;i<(*MaxHeap)->dim;i++){
        int clone=i;
        while(*((*MaxHeap)->vect+clone)>*((*MaxHeap)->vect+clone>>1)&&clone>0){
            int aux=*((*MaxHeap)->vect+clone);
            *((*MaxHeap)->vect+clone)=*((*MaxHeap)->vect+clone>>1);
            *((*MaxHeap)->vect+clone>>1)=aux;
            clone>>=1;
        }
    }
}
