#include <iostream>

using namespace std;

struct BTNode {
    char data;
    BTNode *left, *right;
};

BTNode* createBTNode() {
    BTNode *A = new BTNode[sizeof(BTNode)];
    BTNode *B = new BTNode[sizeof(BTNode)];
    BTNode *C = new BTNode[sizeof(BTNode)];
    BTNode *D = new BTNode[sizeof(BTNode)];
    BTNode *E = new BTNode[sizeof(BTNode)];
    BTNode *F = new BTNode[sizeof(BTNode)];
    BTNode *G = new BTNode[sizeof(BTNode)];

    A->data = 'A';
    B->data = 'B';
    C->data = 'C';
    D->data = 'D';
    E->data = 'E';
    F->data = 'F';
    G->data = 'G';

    // 定位
    A->left = NULL;
    A->right = NULL;

    B->left = A;
    B->right = C;

    C->left = NULL;
    C->right = NULL;

    D->left = B;
    D->right = F;
    
    E->left = NULL;
    E->right = NULL;

    F->left = E;
    F->right = G;

    G->left = NULL;
    G->right = NULL;

    return D;
}

void prePrint(BTNode* root) {
    if(root->left == NULL) return;
    prePrint(root->left);
}

void insertNode(BTNode* root, int data) {
    
}

int main() {
    return 0;
}