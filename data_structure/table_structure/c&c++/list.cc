#include <iostream>

using namespace std;

// 单向顺序表，实现增删改查功能

#define MAXSIZE 100

// 顺序表结构
struct list {
    int *data;
    int size;
};

void init_list(list* l) {
    l->data = new int[MAXSIZE];
    l->size = 0;
    // input data by hands
    while (true)
    {
        int data;
        cout << ">>> ";
        cin >> data;
        if(data == -1) break;
        // insert data
        l->data[l->size++] = data;
    }
}

void delete_list(list* l, int pos) {
    
}

void print(list* l) {
    for(int i = 0; i < l->size; ++i) {
        cout << l->data[i] << endl;
    }
}

int main() {
    list* l = new list[sizeof(list)];
    init_list(l);
    print(l);
    return 0;
}