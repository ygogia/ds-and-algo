#include <stdio.h>
#include <stdlib.h>
#include "tree_queue.h"

struct BinaryTreeNode* createNewNode(int data){
    struct BinaryTreeNode* node = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
void inOrder(struct BinaryTreeNode* root){
    if (root == NULL) // or if (!root)
        return;

    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

void preOrder(struct BinaryTreeNode* root){
    if (root == NULL){
        return;
    }
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);

}

void postOrder(struct BinaryTreeNode* root){
    if (root == NULL){
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);

}

void preOrder_i(struct BinaryTreeNode* root){
    struct DynamicArrayStack *S = CreateTreeStack();
    while(1){
        while(root){
            printf("%d ", root->data);
            PushNode(S, root);
            root=root->left;
        }
        if(IsEmptyTreeStack(S)){
            break;
        }
        root = PopNode(S);
        root=root->right;
    }
    DeleteTreeStack(S);
}
void inOrder_i(struct BinaryTreeNode *root){
    struct DynamicArrayStack *S = CreateTreeStack();
    while(1){
        while(root){
            PushNode(S, root);
            root=root->left;
        }
        if (IsEmptyTreeStack(S)){
            break;
        }
        root = PopNode(S);
        printf("%d ", root->data);
        root = root->right;
    }
    DeleteTreeStack(S);
}

void postOrder_i(struct BinaryTreeNode* root){
    struct DynamicArrayStack *S = CreateTreeStack();
    struct BinaryTreeNode *previous = NULL;
    do{
        while(root!=NULL){
            PushNode(S, root);
            root = root->left;
        }
        while(root==NULL && !IsEmptyTreeStack(S)) {
            root = TopNode(S);
            if (root->right == NULL || root->right == previous) {
                printf("%d ", root->data);
                PopNode(S);
                previous = root;
                root = NULL;
            }else{
                root = root->right;
            }
        }
    }while(!IsEmptyTreeStack(S));

}

void levelOrder(struct BinaryTreeNode *P){
    struct DynamicArrayTreeQueue *Q = CreateTreeQueue();
    struct BinaryTreeNode *temp;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
    if(!P){
        return;
    }
    EnQueue(Q, P);
    while(!IsTreeQueueEmpty(Q)){
        temp = DeQueue(Q);
        left = temp->left;
        right = temp->right;
        int data = temp->data;
        if(left){
            EnQueue(Q, left);
        }
        if(right) {
            EnQueue(Q, right);
        }
        printf("%d ", data);

    }
    DeleteQueue(Q);
}

int largestElement(struct BinaryTreeNode *P){
    int root_val, left, right, max=INT8_MIN;
    if(P!=NULL){
        root_val=P->data;
        right = largestElement(P->right);
        left = largestElement(P->left);

        if (left>right){
            max = left;
        }else{
            max = right;
        }
        if(root_val>max){
            max=root_val;
        }
    }
    return max;
}

int largestElement_i(struct BinaryTreeNode *P){
    int max=INT8_MIN;
    struct DynamicArrayTreeQueue *Q = CreateTreeQueue();
    struct BinaryTreeNode *temp;
    EnQueue(Q, P);
    while(!IsTreeQueueEmpty(Q)){
        temp = DeQueue(Q);
        int data = temp->data;
        if(temp->left){
            EnQueue(Q, temp->left);
        }
        if(temp->right){
            EnQueue(Q, temp->right);
        }
        if(data>max){
            max = data;
        }
    }
    return max;
}

int findInTree(struct BinaryTreeNode *P, int x){
    if(P!=NULL){
        if(x==P->data){
            return 1;
        }
        if(findInTree(P->left, x)){
            return 1;
        }
        if(findInTree(P->right, x)){
            return 1;
        }
    }
    return 0;
}

int findInTree_i(struct BinaryTreeNode *P, int x){
    struct DynamicArrayTreeQueue *Q = CreateTreeQueue();
    struct BinaryTreeNode *temp;
    EnQueue(Q, P);
    while(!IsTreeQueueEmpty(Q)){
        temp = DeQueue(Q);
        if(x == temp->data){
            return 1;
        }
        if( temp->left){
            EnQueue(Q,  temp->left);
        }
        if(temp->right){
            EnQueue(Q, temp->right);
        }
    }
    return 0;
}

void insertInTree(struct BinaryTreeNode *P, int x){
    struct DynamicArrayTreeQueue *Q = CreateTreeQueue();
    struct BinaryTreeNode *temp;
    EnQueue(Q, P);
    struct BinaryTreeNode *newNode = (struct BinaryTreeNode *) malloc(sizeof(struct BinaryTreeNode));
    newNode->data = x;
    newNode->left = NULL;
    newNode->right = NULL;
    if(!newNode){
        return;
    }
    while(!IsTreeQueueEmpty(Q)){
        temp = DeQueue(Q);
        if(temp->left){
            EnQueue(Q, temp->left);
        }else{
            temp->left = newNode;
            return;
        }
        if(temp->right){
            EnQueue(Q, temp->right);
        } else{
            temp->right = newNode;
            return;
        }
    }
}

int size(struct BinaryTreeNode *P){
    if(!P){
        return 0;
    }
    return 1 + size(P->right) + size(P->left);
}
int size_i(struct BinaryTreeNode *P){
    if(!P){
        return 0;
    }
    struct BinaryTreeNode *temp;
    struct DynamicArrayTreeQueue *Q = CreateTreeQueue();
    EnQueue(Q, P);
    int count = 0;
    while(!IsTreeQueueEmpty(Q)){
        temp = DeQueue(Q);
        count++;
        if(temp->left){
               EnQueue(Q, temp->left);
        }
        if(temp->right){
            EnQueue(Q, temp->right);
        }
    }
    return count;
}

int height(struct BinaryTreeNode *P){
    if(!P){
        return 0;
    }
    int left_height, right_height=0;
    left_height = height(P->left);
    right_height = height(P->right);
    if(left_height>right_height){
        return left_height+1;
    }else{
        return right_height+1;
    }
}

int height_i(struct BinaryTreeNode *P){
    struct DynamicArrayTreeQueue *Q = CreateTreeQueue();
    struct BinaryTreeNode *temp;
    int count = 0;
    EnQueue(Q, P);
    EnQueue(Q, NULL);
    while (!IsTreeQueueEmpty(Q)){
        temp = DeQueue(Q);
        if(!temp){
            count++;
            if(!IsTreeQueueEmpty(Q)) {
                EnQueue(Q, NULL);
            }
        }else{
            if(temp->right){
                EnQueue(Q, temp->right);
            }else if(temp->left){
                EnQueue(Q, temp->left);
            }
        }
    }
    return count;
}

int deepest_node(struct BinaryTreeNode *P){
    struct DynamicArrayTreeQueue *Q = CreateTreeQueue();
    struct BinaryTreeNode *temp;
    EnQueue(Q, P);
    while (!IsTreeQueueEmpty(Q)){
        temp = DeQueue(Q);
        if(temp->right){
            EnQueue(Q, temp->right);
        }
        if(temp->left){
            EnQueue(Q, temp->left);
        }
    }
    return temp->data;
}

int delete_node(struct BinaryTreeNode *P, int x){
    struct DynamicArrayTreeQueue *Q = CreateTreeQueue();
    struct BinaryTreeNode *temp;
    struct BinaryTreeNode *tbd;
    EnQueue(Q, P);
    while (!IsTreeQueueEmpty(Q)){;
        temp = DeQueue(Q);
        if(temp->data == x){
            tbd = temp;
        }
        if(temp->right){
            EnQueue(Q, temp->right);
        }
        if(temp->left) {
            EnQueue(Q, temp->left);
        }
    }
    tbd->data = temp->data;
    free(temp);
    return 0;
}

int leaves(struct BinaryTreeNode *P){
    struct DynamicArrayTreeQueue *Q = CreateTreeQueue();
    struct BinaryTreeNode *temp;
    EnQueue(Q, P);
    int count = 0;
    while (!IsTreeQueueEmpty(Q)){;
        temp = DeQueue(Q);
        if(temp->right){
            EnQueue(Q, temp->right);
        }
        if(temp->left) {
            EnQueue(Q, temp->left);
        }
        if(temp->right==NULL && temp->left==NULL){
            count++;
        }
    }
    free(temp);
    return count;
}
int full_nodes(struct BinaryTreeNode *P){
    struct DynamicArrayTreeQueue *Q = CreateTreeQueue();
    struct BinaryTreeNode *temp;
    EnQueue(Q, P);
    int count = 0;
    while (!IsTreeQueueEmpty(Q)){;
        temp = DeQueue(Q);
        if(temp->right){
            EnQueue(Q, temp->right);
        }
        if(temp->left) {
            EnQueue(Q, temp->left);
        }
        if(temp->right!=NULL && temp->left!=NULL){
            count++;
        }
    }
    free(temp);
    return count;
}

int half_nodes(struct BinaryTreeNode *P){
    struct DynamicArrayTreeQueue *Q = CreateTreeQueue();
    struct BinaryTreeNode *temp;
    EnQueue(Q, P);
    int count = 0;
    while (!IsTreeQueueEmpty(Q)){;
        temp = DeQueue(Q);
        if(temp->right){
            EnQueue(Q, temp->right);
        }
        if(temp->left) {
            EnQueue(Q, temp->left);
        }
        if((temp->right==NULL && temp->left!=NULL)||(temp->right!=NULL && temp->left==NULL)){
            count++;
        }
    }
    free(temp);
    return count;
}

int are_identical(struct BinaryTreeNode *tree1, struct BinaryTreeNode *tree2){
    struct DynamicArrayTreeQueue *queue1 = CreateTreeQueue();
    struct DynamicArrayTreeQueue *queue2 = CreateTreeQueue();
    struct BinaryTreeNode *temp1;
    struct BinaryTreeNode *temp2;
    EnQueue(queue1, tree1);
    EnQueue(queue2, tree2);
    int count = 0;
    int is_similar = 0;
    while (!IsTreeQueueEmpty(queue1) && !IsTreeQueueEmpty(queue2)) {
        is_similar=1;
        temp1 = DeQueue(queue1);
        temp2 = DeQueue(queue2);
        if ((temp1->right && temp2->right)&&(temp1->right->data==temp2->right->data)) {
            EnQueue(queue1, temp1->right);
            EnQueue(queue2, temp2->right);
        }else if(!temp1->right && !temp2->right);
        else{
            is_similar=0;
            break;
        }
        if ((temp1->left && temp2->left)&&(temp1->left->data==temp2->left->data)) {
            EnQueue(queue1, temp1->left);
            EnQueue(queue2, temp2->left);
        }else if(!temp1->left && !temp2->left);
        else{
            is_similar=0;
            break;
        }
    }
    return is_similar;
}


int testInOrder(){
    /* Sample binary tree is
            9
          /   \
        19      1
         \    /
          3  6
    */
    struct BinaryTreeNode* root = createNewNode(9);
    root->left        = createNewNode(19);
    root->right       = createNewNode(1);
    struct BinaryTreeNode* temp = root->left;
    temp->right  = createNewNode(3);
    temp = root->right;
    temp->left = createNewNode(6);

    struct BinaryTreeNode* root2 = createNewNode(9);
    root2->left        = createNewNode(19);
    root2->right       = createNewNode(1);
    struct BinaryTreeNode* temp2 = root2->left;
    temp2->right  = createNewNode(3);
//    temp2->left  = createNewNode(5);
    temp2 = root2->right;
    temp2->left = createNewNode(6);
//    inOrder_i(root);
//    postOrder(root);
//    preOrder_i(root);
//    levelOrder(root);
//    printf("%d",largestElement(root));
//    printf("%d",largestElement_i(root));
//    printf("%d",findInTree_i(root, 6));
//    printf("%d",findInTree(root, 19));
//    insertInTree(root, 10);
//    printf("%d",findInTree_i(root, 10));
//    printf("%d",size(root));
//    printf("%d",size_i(root));
//    printf("%d",height(root));
//    printf("%d",height_i(root));
//    printf("%d",deepest_node(root));
//    delete_node(root, 19);                                //PROBLEMATIC
//    printf("%d",leaves(root));
//    printf("%d",full_nodes(root));
//    printf("%d",half_nodes(root));
//    printf("%d",are_identical(root, root2));

    return 0;
}