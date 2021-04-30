#include <iostream>

using namespace std;

#define INF 0xFFFFFFFF  // 无穷大
int n = 4;

// 显示函数，传入邻接矩阵，行数和列数
void display(int mat[][4], int rows, int cols) {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

// 广度优先算法，先遍历列，再遍历行
void BFSN(char V[], int mat[][4]) { // 传入顶点和邻接矩阵
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {    // j==i
            if(mat[j][i] != 0 && mat[j][i] != INF)  // 不等于0和无穷大进行打印
                printf("%c->%c weight=%d\t", V[i], V[j], mat[j][i]);
        }
        cout << endl;
    }
}

// 深度优先算法，先遍历行，再遍历列
void DFSN(char V[], int mat[][4]) {
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            if(mat[i][j] != 0 && mat[i][j] != INF)  // 不等于无穷大和0时进行打印
                printf("%c->%c weight=%d\t", V[j], V[i], mat[i][j]);
        }
        cout << endl;
    }
}

int main() {
    char V[4] = {'A', 'B', 'C', 'D'};   // 图的顶点
    int mat[][4] = {    // 图的邻接矩阵
        {0, 2, 5, 7},
        {2, 0, 6, 3},
        {5, 6, 0, 1},
        {7, 3, 1, 0}
    };
    display(mat, 4, 4);
    BFSN(V, mat);
    cout << "*************" << endl;
    display(mat, 4, 4);
    DFSN(V, mat);
    return 0;
}