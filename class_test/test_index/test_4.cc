#include <iostream>

using namespace std;

// 定义结构体，Root == *Node，代指二叉树
typedef struct Node {
    char data;
    Node *left;
    Node *right;
} Node, *Root;

// 辅助函数，创建一个已经初始化了的节点
Node *create_node(int data) {
    Node *node = new Node[sizeof(Node)];
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Root init(char data) {
    return create_node(data);
}

// 将节点插入二叉树中
void locate(Root root, Node *node) {
    if ((int)node->data < (int)root->data) {    //节点的data要是小于root的data往左边插入
        if (root->left == NULL) {   //左子树为空，直接插入
            root->left = node;
            return;
        }
        locate(root->left, node);   //非空，递归调用，继续在左子树寻找位置
    } else {    //往右边插入
        if (root->right == NULL) {  //右子树为空，直接插入
            root->right = node;
            return;
        }
        locate(root->right, node);  //非空，递归调用，继续在右子树寻找位置
    }
}

void insert_node(Root root, int data) {
    Node *node = create_node(data); //创建一个节点
    locate(root, node); //给节点找到一个合适的位置并插入二叉树
}

// 先访问根，再访问左子树，再访问右子树
void prePrint(Root root) {
    if (root == NULL) return;
    cout << root->data << " ";
    prePrint(root->left);
    prePrint(root->right);
}

// 先访问左子树，再访问根，再访问右子树
void middlePrint(Root root) {
    if (root == NULL) return;
    middlePrint(root->left);
    cout << root->data << " ";
    middlePrint(root->right);
}

// 先访问右子树，再访问左子树，再访问根
void postPrint(Root root) {
    if(root == NULL) return;
    postPrint(root->left);
    postPrint(root->right);
    cout << root->data << " ";
}

int main() {
    char str[] = {'D', 'B', 'A', 'C', 'F', 'E', 'G'};
    Root root = init(str[0]);
    for(int i = 1; i < 7; ++i) {
        insert_node(root, str[i]);
    }

    cout << "先根遍历：";
    prePrint(root);
    cout << '\n';

    cout << "中根遍历：";
    middlePrint(root);
    cout << '\n';

    cout << "后根遍历：";
    postPrint(root);
    cout << '\n';
    return 0;
}