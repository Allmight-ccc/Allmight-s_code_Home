#include <iostream>

using namespace std;

struct Node {
    char data;
    int weight;
    Node *left;
    Node *right;
};

void init(Node **nodes, char *datas, int *weights, int length) {
    for(int i = 0; i < length; ++i) {
        Node* node = new Node[sizeof(Node)];
        node->data = datas[i];
        node->left = NULL;
        node->right = NULL;
        nodes[i] = node;
    }
}

void getMinSecond(Node **nodes, int& min1, int& min2, int length) {
    while(nodes[min1] == 0) {
        min1++;
        min2++;
    }
    while(nodes[min2] == 0) min2++;
    for(int i = min2; i < length; ++i) {
        if(nodes[i] != 0) {
            if(nodes[i]->weight < nodes[min1]->weight) {
                min2 = min1;
                min1 = i;
            } else if(nodes[i]->weight < nodes[min2]->weight) {
                min2 = i;
            }
        }
    }
}

Node* createHalfman(Node** nodes, char* datas, int* weights, int length) {
    init(nodes, datas, weights, length);
    Node* root;
    for(int i = 0; i < length; ++i) {
        int min1 = 0, min2 = 1;
        getMinSecond(nodes, min1, min2, length);
        root = new Node[sizeof(Node)];
        root->data = i+48;
        root->weight = nodes[min1]->weight + nodes[min2]->weight;
        root->left = nodes[min1];
        root->right = nodes[min2];
        nodes[min1] = root;
        nodes[min2] = NULL;
    }
    return root;
}

int main() {
    int length = 7;
    Node **nodes = new Node*[length];

    char datas[] = {};
    int weights[] = {};
}