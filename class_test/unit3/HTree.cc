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
        node->weight = weights[i];
        node->left = NULL;
        node->right = NULL;
        nodes[i] = node;
    }
}



void createHalfman() {

}

int main() {
    int length = 7;
    Node **nodes = new Node*[length];

    char datas[] = {};
    int weights[] = {};
}