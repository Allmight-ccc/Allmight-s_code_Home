#include <iostream>

using namespace std;

typedef struct Node {
    char data;
    Node *left;
    Node *right;
} Node, *Tree;

Node *create_node(int data) {
    Node *node = new Node[sizeof(Node)];
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Tree init(char data) {
    return create_node(data);
}

void locate(Tree tree, Node *node) {
    if ((int)node->data < (int)tree->data) {
        if (tree->left == NULL) {
            tree->left = node;
            return;
        }
        locate(tree->left, node);
    } else {
        if (tree->right == NULL) {
            tree->right = node;
            return;
        }
        locate(tree->right, node);
    }
}

void insert_node(Tree tree, int data) {
    Node *node = create_node(data);
    locate(tree, node);
}

// 先访问根，再访问左子树，再访问右子树
void prePrint(Tree tree) {
    if (tree == NULL) return;
    cout << tree->data << " ";
    prePrint(tree->left);
    prePrint(tree->right);
}

// 先访问左子树，再访问根，再访问右子树
void middlePrint(Tree tree) {
    if (tree == NULL) return;
    middlePrint(tree->left);
    cout << tree->data << " ";
    middlePrint(tree->right);
}

// 先访问右子树，再访问左子树，再访问根
void postPrint(Tree tree) {
    if(tree == NULL) return;
    postPrint(tree->left);
    postPrint(tree->right);
    cout << tree->data << " ";
}

int main() {
    char str[] = {'D', 'B', 'A', 'C', 'F', 'E', 'G'};
    Tree tree = init(str[0]);
    for(int i = 1; i < 7; ++i) {
        insert_node(tree, str[i]);
    }
    middlePrint(tree);
    return 0;
}