#include <iostream>

using namespace std;

typedef struct node
{
    int data;
    node *preious, *next;
}node, *linkdList;

linkdList init() {
    linkdList l = new node[sizeof(node)];
    l->preious = NULL;
    l->next = NULL;
    return l;
}

void insert_node(linkdList l, int data) {
    
}

int main() {
    return 0;
}