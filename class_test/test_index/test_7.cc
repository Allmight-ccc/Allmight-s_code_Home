#include <iostream>

using namespace std;

#define INF 0xFFFFFFFF
int n = 4;

void display(int mat[][4], int rows, int cols) {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

void BFSN(char V[], int mat[][4]) {
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            if(mat[j][i] != 0 && mat[j][i] != INF)
                printf("%c->%c weight=%d\t", V[i], V[j], mat[j][i]);
        }
        cout << endl;
    }
}

void DFSN(char V[], int mat[][4]) {
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            if(mat[i][j] != 0 && mat[i][j] != INF)
                printf("%c->%c weight=%d\t", V[j], V[i], mat[i][j]);
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
    display(mat, 4, 4);
    BFSN(V, mat);
    cout << "*************" << endl;
    display(mat, 4, 4);
    DFSN(V, mat);
    return 0;
}