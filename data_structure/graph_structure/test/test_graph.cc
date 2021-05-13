#include <iostream>

using namespace std;

#define INF 0xFFFFFFFF
int n = 4;

void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

void swapVetex(char vetexs[], int VetexSize, int mat[][4], int start) {
    swap(vetexs[0], vetexs[start]);
    for(int i = 0; i < VetexSize; ++i)
        swap(mat[i][start], mat[i][0]);
    for(int i = 0; i < VetexSize; ++i)
        swap(mat[start][i], mat[0][i]);
}

void display(int mat[][4], int rows, int cols) {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void BFSN(char V[], int mat[][4]) {
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            if(mat[j][i] != 0 && mat[j][i] != INF) {
                printf("%c->%c weight=%d\t", V[i], V[j], mat[j][i]);
            }
        }
        cout << endl;
    }
}

void DFSN(char V[], int mat[][4]) {
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            if(mat[i][j] != 0 && mat[i][j] != INF) {
                printf("%c->%c weight=%d", V[j], V[i], mat[i][j]);
            }
        }
        cout << endl;
    }
}

int main() {
    char V[4] = {'A', 'B', 'C', 'D'};
    int mat[][4] = {
        {0, 2, 5, 7},
        {2, 0, 6, 3},
        {5, 6, 0, 1},
        {7, 3, 1, 0}
    };
    swapVetex(V, sizeof(V)/sizeof(char), mat, 3);
    display(mat, 4, 4);
    BFSN(V, mat);
    return 0;
}