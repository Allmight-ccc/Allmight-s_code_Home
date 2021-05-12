#include <iostream>
#define N 4

using namespace std;

void display(char* v, int* p, int size) {
    for(int i = 0; i < size; ++i)
        cout << v[p[i]] << " ";
    cout << endl;
}

void swap(int* v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void perm(char* v, int* p, int first, int last) {
    for(int i = first; i <= last; ++i) {
        if(i != first) swap(p, p[first], p[i]); // 依次取每一个元素为前一个元素
        perm(v, p, first+1, last);  // 递归
        if(i != first) swap(p, p[first], p[i]); // 还原数据
    }
    if(first == last) display(v, p, N);
}



int main() {
    char v[] = "ABCD";
    int p[] = {0, 1, 2, 3};
    // swap(v, 0, 2);
    // display(v, N);
    perm(v, p, 1, 3);
    return 0;
}