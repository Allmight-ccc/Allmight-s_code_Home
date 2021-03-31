#include <iostream>

using namespace std;

struct BTNode {
    char data;
    BTNode *left;
    BTNode *right;
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
    if(root == NULL) return;
    cout << root->data << " ";
    prePrint(root->left);
    prePrint(root->right);
}

void middlePrint(BTNode* root) {
    if(root == NULL) return;
    middlePrint(root->left);
    cout << root->data << " ";
    middlePrint(root->right);
}

void lastPrint(BTNode* root) {
    if(root == NULL) return;
    lastPrint(root->left);
    lastPrint(root->right);
    cout << root->data << " ";
}

void insertNode(BTNode* root, int data) {
    // init node
    BTNode *node = new BTNode[sizeof(BTNode)];
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    BTNode *temp = root;
    if(temp == NULL) {
        temp = node;
        return;
    }

    //

    if(temp->left == NULL) {
        temp->left = node;
    } else if(temp->right == NULL) {
        temp->right = node;
    }
}

int get_height(BTNode* root) {
    int result;
    BTNode* temp = root;
    for(result = 1; temp = temp->left; ++result);
    return result;
}

int get_leave(BTNode* root) {
    
}

int main() {
    BTNode* root = createBTNode();
    prePrint(root);
    cout << "\n" << endl;
    middlePrint(root);
    cout << "\n" << endl;
    lastPrint(root);
    cout << "\n" << endl;
    cout << get_height(root) << endl;
    return 0;
}