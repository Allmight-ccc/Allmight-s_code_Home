#include <iostream>
#define N 4

using namespace std;

void display(char* v, int* p, int size) {
    for(int i = 0; i < size; ++i)
        cout << v[p[i]] << " ";
    cout << endl;
}

void display(int* p, int size) {
    for(int i = 0; i < size; ++i)
        cout << p[i] << " ";
    cout << endl;
}

void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

void swapVetex(char vetexs[], int VetexSize, int mat[][N], int start) {
    swap(vetexs[0], vetexs[start]);
    for(int i = 0; i < VetexSize; ++i) swap(mat[i][start], mat[0][i]);
    for(int i = 0; i < VetexSize; ++i) swap(mat[start][i], mat[i][0]);
}

void swap(int* v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void perm(int c[][N], char* v, int* p, int first, int last, int *min, int *n) {
    for(int i = first; i <= last; ++i) {
        if(i != first) swap(p, p[first], p[i]); // 依次取每一个元素为前一个元素
        perm(c, v, p, first+1, last, min, n);  // 递归
        if(i != first) swap(p, p[first], p[i]); // 还原数据
    }
    if(first == last) {
        int sum;
        for(int i = 0; i <= last; ++i) {
            sum = 0;
            for(int j = 0; j < last; ++j) sum += c[p[j]][p[j+1]];
            sum += c[p[last]][0];
            cout << v[p[i]] << " ";
        }
        cout << v[0] << " 路径的长度：" << sum << endl;
        if(sum < *min) *min = sum;
        *n += 1;
    }
}



int main() {
    char v[] = "ABCD";
    // p是为了邻接矩阵
    int p[] = {0, 1, 2, 3};
    // swap(v, 0, 2);
    // display(v, N);
    int c[][N] = {
        {0, 2, 5, 7},
        {2, 0, 8, 3},
        {5, 8, 0, 1},
        {7, 3, 1, 0}
    };
    int c1[][N] = {
        {0, 1, 2, 3},
        {5, 0, 2, 3},
        {6, 4, 0, 2},
        {9, 2, 7, 0}
    };
    int n = 0;
    int min = 0xFFFFFFF;
    perm(c1, v, p, 1, 3, &min, &n);

    cout << "*********************" << endl;
    int p1[] = {0, 1, 2, 3};
    n = 0;
    min = 0xFFFFFFF;
    swapVetex(v, N, c, 1);
    perm(c1, v, p1, 1, 3, &min, &n);

    cout << "*********************" << endl;
    int p2[] = {0, 1, 2, 3};
    n = 0;
    min = 0xFFFFFFF;
    swapVetex(v, N, c, 2);
    perm(c1, v, p2, 1, 3, &min, &n);

    cout << "*********************" << endl;
    int p3[] = {0, 1, 2, 3};
    n = 0;
    min = 0xFFFFFFF;
    swapVetex(v, N, c, 3);
    perm(c1, v, p3, 1, 3, &min, &n);
    return 0;
}