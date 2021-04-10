#include <iostream>

using namespace std;

typedef struct node
{
    int data;
    node *previous, *next;
}node, *linkdList;

linkdList init() {
    linkdList l = new node[sizeof(node)];
    l->previous = NULL;
    l->next = NULL;
    return l;
}

// 尾插法
void insert_node(linkdList& tail, int data) {
    node* n = new node[sizeof(node)];
    n->data = data;
    n->next = tail->next;
    tail->next = n;
    n->previous = tail;
    tail = n;
}

// 删除链表中的数据
void delete_node(linkdList& l, int data) {
    node* p = l->next;
    while (p) {
        if(p->next && p->next->data == data) {
            node* q = p->next;
            p->next = q->next;
            delete(q);
        }
        p = p->next;
    }
}

// 更新某个节点的信息
void update_node(linkdList& l, int data, int new_data) {
    node* p = l->next;
    while (p) {
        if(p->data == data) {
            p->data = new_data;
        }
        p = p->next;
    }
}

// 查找数据，返回相应节点
node* search_node(linkdList& l, int data) {
    node* n = l->next;
    while (n) {
        if(n->data = data) {
            return n;
        }
        n = n->next;
    }
    return NULL;
}

// 顺序打印
void print_linkdList_head(linkdList head) {
    node* n = head;
    cout << "顺序打印链表结果：";
    while (n = n->next)
        cout << n->data << " ";
    cout << endl;
}

// 逆序打印
void print_linkdList_tail(linkdList tail) {
    node* n = tail;
    cout << "逆序打印链表结果：";
    do{
        cout << n->data << " ";
        n = n->previous;
    }while(n->previous);
    cout << endl;
}

int main() {
    // 测试代码
    linkdList head, tail;
    head = tail = init();   //初始化头节点和尾节点
    for(int i = 0; i < 10; ++i) {
        insert_node(tail, i);   //循环插入十个节点
    }
    print_linkdList_head(head); //顺序打印结果
    print_linkdList_tail(tail); //逆序打印结果

    delete_node(head, 3);
    print_linkdList_head(head);

    update_node(head, 4, 100);
    print_linkdList_head(head);

    node* n = search_node(head, 100);
    cout << "查找到的节点数据：" << n->data << endl;
    return 0;
}