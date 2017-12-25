//
// Created by Yogesh Gogia on 8/15/17.
//

#ifndef DS_AND_ALGO_STRUCTURES_H
#define DS_AND_ALGO_STRUCTURES_H

#endif //DS_AND_ALGO_STRUCTURES_H

struct BinaryTreeNode{
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
};


struct DynamicArrayStack{
    int top;
    int capacity;
    struct BinaryTreeNode *array;
};

struct DynamicArrayTreeQueue{
    int front;
    int rear;
    int capacity;
    struct BinaryTreeNode **array;
};