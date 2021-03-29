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

bool delete_list(list* l, int index) {
    if(index > l->size && index < 0) return false;

    // 删除元素
    for(int i = index; i < l->size; ++i) {
        l->data[i] = l->data[i+1];
    }
    l->size--;
    return true;
}

bool update_list(list* l, int index, int data) {
    if(index > l->size && index < 0) return false;

    l->data[index] = data;
    return true;
}

// 返回最先找到该数据的索引
int find_element(list* l, int data) {
    int index = 0;
    while (l->data[index++] != data);
    return (index < l->size) ? index : -1;
}

// 打印list
void print(list* l) {
    for(int i = 0; i < l->size; ++i) {
        cout << l->data[i] << " ";
    }
    cout << endl;
}

int main() {
    list* l = new list[sizeof(list)];
    init_list(l);
    print(l);
    delete_list(l, 0);
    print(l);

    cout << find_element(l, 100) << endl;
    return 0;
}