#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "structures.h"

struct DynamicArrayStack *CreateTreeStack(){
    struct DynamicArrayStack *S = malloc(sizeof(struct DynamicArrayStack));
    if(!S){
        return NULL;
    }
    S->top = -1;
    S->capacity = 1;
    S->array = malloc(S->capacity*sizeof(struct BinaryTreeNode));

    if(!S->array){
        return NULL;
    }
    return S;
}

int IsEmptyTreeStack(struct DynamicArrayStack *S){
    return S->top == -1;
}

int IsFullTreeStack(struct DynamicArrayStack *S){
    return (S->top == S->capacity-1);
}

void DoubleTreeStack(struct DynamicArrayStack *S){
    S->capacity *= 2;
    S->array = realloc(S->array, S->capacity*sizeof(struct BinaryTreeNode));
}

void PushNode(struct DynamicArrayStack *S, struct BinaryTreeNode *node){
    if(IsFullTreeStack(S)){
        DoubleTreeStack(S);
    }
    S->array[++S->top] = *node;
}

struct BinaryTreeNode *TopNode(struct DynamicArrayStack *S){
    if(IsEmptyTreeStack(S)){
        return NULL;
    }
    return &S->array[S->top];
}

struct BinaryTreeNode *PopNode(struct DynamicArrayStack *S){
    if(IsEmptyTreeStack(S)){
        return NULL;
    }
    return &S->array[S->top--];
}

void DeleteTreeStack(struct DynamicArrayStack *S){
    if(S){
        if(S->array){
            free(S->array);
        }
        free(S);
    }
}