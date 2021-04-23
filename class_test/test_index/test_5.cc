#include <iostream>

using namespace std;

// 声明节点
struct Node {
    char data;
    int weight; // 权重
    Node *left;
    Node *right;
};

// 将每一个节点初始化
void init(Node **nodes, char *datas, int *weights, int length) {
    for(int i = 0; i < length; ++i) {
        Node* node = new Node[sizeof(Node)];
        node->weight = weights[i];
        node->data = datas[i];
        node->left = NULL;
        node->right = NULL;
        nodes[i] = node;
    }
}

// 获取最小值和次小值
void getMinSecond(Node **nodes, int& min1, int& min2, int length) {
    while(nodes[min1] == NULL) {
        min1++;
        min2++;
    }
    while(nodes[min2] == NULL) min2++;
    for(int i = min2; i < length; ++i) {
        if(nodes[i] != NULL) {
            if(nodes[i]->weight < nodes[min1]->weight) {
                min2 = min1;    // 更新次小值的位置
                min1 = i;   // 更新最小值的位置
            } else if(nodes[i]->weight < nodes[min2]->weight) {
                min2 = i;   // 更新次小值的位置
            }
        }
    }
}

//  创建哈夫曼树
Node* createHalfman(Node** nodes, char* datas, int* weights, int length) {
    // 初始化创建哈夫曼树的数据
    init(nodes, datas, weights, length);
    Node* root;
    for(int i = 1; i < length; ++i) {
        int min1 = 0, min2 = 1;
        getMinSecond(nodes, min1, min2, length);    // 获得权重最小和次小的节点的索引
        root = new Node[sizeof(Node)];
        root->weight = nodes[min1]->weight + nodes[min2]->weight;   // 更新权重
        root->data = i+48;  // 更新数据，从一开始
        root->left = nodes[min1];   //  更新左子树
        root->right = nodes[min2];  // 更新右子树
        nodes[min1] = root; // 将最小权重的节点更新为root节点
        nodes[min2] = NULL; // 将次小值的值更新为NULL
    }
    return root;
}

// 先根遍历
void prePrint (Node* root){
    if(root==NULL)return;
    cout << root->data << " " << root->weight << endl;
    prePrint(root->left);
    prePrint(root->right);
}

int main() {
    int length = 7;
    Node **nodes = new Node*[length];

    char datas[] = {'A', 'D', 'B', 'C', 'R', 'E', 'G'};
    int weights[] = {12, 3, 43, 2, 13, 54, 32};
    Node* root = createHalfman(nodes, datas, weights, length);

    cout << "中根遍历：" << endl;
    prePrint(root);
    return 0;
}