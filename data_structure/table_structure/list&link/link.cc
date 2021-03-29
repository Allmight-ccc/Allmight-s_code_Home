#include <iostream>

using namespace std;

// 单向链表，实现增删改查功能


// 单个节点
typedef struct node {
    int data;
    node *next;
}node, *linkList;

linkList init() {
    linkList l = new node[sizeof(node)];
    l->next = NULL;
    return l;
}

void insert_node(linkList l, int data) {
    node* n = new node[sizeof(node)];
    n->data = data;
    n->next = NULL;
    l->next = n;
}

// 删除所有数据为data的节点
void delete_node(linkList l, int data) {
    node* p = l->next;
    while(p) {
        if(p->next->data == data) {
            node* q = p->next;
            p->next = q->next;
            delete(q);
        }
        p = p->next;
    }
}

void update_node(linkList l, int data, int new_data) {
    node* p = l->next;
    while(p) {
        if(p->data == data) {
            p->data = new_data;
            break;
        }
        p = p->next;
    }
}

node* search_node(linkList l, int data) {
    node* n = l->next;
    while (n) {
        if(n->data = data) {
            return n;
        }
        n = n->next;
    }
    return NULL;
}

int main() {

    return 0;
}