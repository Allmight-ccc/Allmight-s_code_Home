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

void insert_node(linkdList l, int data) {
    node* n = new node[sizeof(node)];
    n->data = data;
    l->next = n;
    n->previous = l;
    n->next = NULL;
}

// ToDo
void delete_node(linkdList l, int data) {
    node* p = l->next;
    while (p) {
        if(p->next != NULL && p->next->data == data) {
            //delete code
        }else if(p->data == data) {
            
        }
        p = p->next;
    }
}

void update_node(linkdList l, int data, int new_data) {
    node* p = l->next;
    while (p) {
        if(p->data == data) {
            p->data = new_data;
        }
        p = p->next;
    }
}

node* search_node(linkdList l, int data) {
    node* n = l->next;
    while (n) {
        if(n->data = data) {
            return n;
        }
        n = n->next;
    }
    return NULL;
}

void print_linkdList(linkdList l) {
    node* n = l;
    while (n = n->next) {
        cout << n->data << " ";
    }
    cout << endl;
}

int main() {
    return 0;
}