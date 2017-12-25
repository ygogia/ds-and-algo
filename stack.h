#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "structures.h"

struct DynamicArrayStack *CreateStack(){
    struct DynamicArrayStack *S = malloc(sizeof(struct DynamicArrayStack));
    if(!S){
        return NULL;
    }
    S->top = -1;
    S->capacity = 1;
    S->array = malloc(S->capacity*(sizeof(int)));

    if(!S->array){
        return NULL;
    }
    return S;
}

int IsEmptyStack(struct DynamicArrayStack *S){
    return S->top == -1;
}

int IsFullStack(struct DynamicArrayStack *S){
    return (S->top == S->capacity-1);
}

void DoubleStack(struct DynamicArrayStack *S){
    S->capacity *= 2;
    S->array = realloc(S->array, S->capacity*sizeof(int));
}

void Push(struct DynamicArrayStack *S, int data){
    if(IsFullStack(S)){
        DoubleStack(S);
    }
    S->array[++S->top] = data;
}

int Top(struct DynamicArrayStack *S){
    if(IsEmptyStack(S)){
        return INT8_MIN;
    }
    return S->array[S->top];
}

int Pop(struct DynamicArrayStack *S){
    if(IsEmptyStack(S)){
        return INT8_MIN;
    }
    return S->array[S->top--];
}

void DeleteStack(struct DynamicArrayStack *S){
    if(S){
        if(S->array){
            free(S->array);
        }
        free(S);
    }
}

void testStack(){
    struct DynamicArrayStack *s = CreateStack();
    Push(s, 1);
    Push(s, 2);
    Push(s, 3);
    Push(s, 4);
    Push(s, 5);
    Push(s, 6);
    Push(s, 7);
    Push(s, 8);
    Push(s, 9);
    Push(s, 10);

    while (!IsEmptyStack(s)){
        printf("%d\n", Pop(s));
    }
    DeleteStack(s);
}