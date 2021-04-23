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

void getMinSecond(Node **nodes, int *min1, int *min2, int length) {
    while (nodes[*min1] == NULL) {
        (*min1)++;
        (*min2)++;
    }
    while(nodes[*min2] == NULL) (*min2)++;

    for(int i = *min2; i < length; ++i) {

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