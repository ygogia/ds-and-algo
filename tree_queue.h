//
// Created by Yogesh Gogia on 8/15/17.
//

#ifndef DS_AND_ALGO_TREE_QUEUE_H_H
#define DS_AND_ALGO_TREE_QUEUE_H_H

#endif //DS_AND_ALGO_TREE_QUEUE_H_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "tree_stack.h"

struct DynamicArrayTreeQueue* CreateTreeQueue(){
    struct DynamicArrayTreeQueue *Q = malloc(sizeof(struct DynamicArrayTreeQueue));
    if(!Q){
        printf("Memory Error");
        return NULL;
    }
    Q->capacity = 1;
    Q->front = -1;
    Q->rear = -1;
    Q->array = malloc(Q->capacity*(sizeof(struct BinaryTreeNode *)));
    if(!Q->array){
        printf("Memory Error");
    }
    return Q;
}

int IsTreeQueueEmpty(struct DynamicArrayTreeQueue *Q){
    return Q->front==-1;
}

int IsTreeQueueFull(struct DynamicArrayTreeQueue *Q){
    return ((Q->rear+1)%Q->capacity==Q->front);
}

int TreeQueueSize(struct DynamicArrayTreeQueue *Q){
    return (Q->capacity - Q->front + Q->rear+1 )%Q->capacity;
}

void ResizeQueue(struct DynamicArrayTreeQueue *Q){
    int size = Q->capacity;
    int i=0;
    Q->capacity = Q->capacity*2;
    Q->array = realloc(Q->array, Q->capacity*(sizeof(struct BinaryTreeNode*)));
    if(!Q->array){
        printf("Memory Error!");
        return;
    }
    if(Q->front > Q->rear){
        for(i=0; i<Q->front; i++){
            Q->array[i+size] = Q->array[i];
        }
        Q->rear = Q->rear + size;
    }
}

void EnQueue(struct DynamicArrayTreeQueue *Q, struct BinaryTreeNode *data){
    if(IsTreeQueueFull(Q)){
        ResizeQueue(Q);
    }
    Q->rear = (Q->rear+1)%Q->capacity;
    Q->array[Q->rear] = data;
    if(Q->front==-1){
        Q->front = Q->rear;
    }
}

struct BinaryTreeNode *DeQueue(struct DynamicArrayTreeQueue *Q){
    if(IsTreeQueueEmpty(Q)){
        return NULL;
    }
    struct BinaryTreeNode *P = Q->array[Q->front];
    if(Q->front==Q->rear){
        Q->front = -1;
        Q->rear = -1;
    }else {
        Q->front = (Q->front + 1) % Q->capacity;
    }
    return P;
}

void DeleteQueue(struct DynamicArrayTreeQueue *Q){
    if(Q){
        if(Q->array){
            free(Q->array);
        }
        free(Q);
    }
}