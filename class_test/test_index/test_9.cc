#include <iostream>

using namespace std;

#define N 4
#define INF 0x0FFFFFFF

void display(char vetexts[], int distance[], int startPoint[], int size, char word) {
    cout << "从" << word << "点到各点的距离为：";
    for(int i = 0; i < N; ++i) {
        if(i == N-1) { 
            cout << distance[i] << endl;
            break;
        }
        cout << distance[i] << "==>";
    }
    cout << endl;
}

void displayMatrix(int matrix[][N], int shape[2]) {
    for(int i = 0; i < shape[0]; ++i) {
        for(int j = 0; j < shape[1]; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void swapMatrix(char vetexs[], int VetexSize, int mat[][N], int start) {
    swap(vetexs[0], vetexs[start]);
    for(int i = 0; i < VetexSize; ++i) swap(mat[i][start], mat[i][0]);
    for(int i = 0; i < VetexSize; ++i) swap(mat[start][i], mat[0][i]);
}

void initDistance(int distance[], int matrix[][N], int startPoint[]) {
    for(int i = 0; i < N; ++i) {
        startPoint[i] = 0;
        distance[i] = matrix[0][i];
    }
}

int getMinDistance(int distance[]) {
    int min = INF, min_index;
    for(int i = 0; i < N; ++i) {
        if(distance[i] < min) {
            min = distance[i];
            min_index = i;
        }
    }
    return min_index;
}

int Min(int a, int b) {
    return a>b ? b : a;
}

void updateDistance(int matrix[][N], int distance[], int startPoint[], int min_index) {
    for(int i = 0; i < N; ++i) {
        if(distance[min_index] < distance[i]) {
            distance[i] = matrix[min_index][i];
            startPoint[i] = min_index;
        }
    }
}

void prim(char vetexs[], int matrix[][N], int distance[], int startPoint[]) {
    initDistance(distance, matrix, startPoint);
    for(int i = 0; i < N-1; ++i) {
        int min_index = getMinDistance(distance);
        updateDistance(matrix, distance, startPoint, min_index);
    }
}

int main() {
    char vetexs[] = "ABCD";
    int matrix[][N] = {
        {0, 2, 5, 7},
        {2, 0, 8, 3},
        {5, 8, 0, 1},
        {7, 3, 1, 0}
    };
    int distance[N] = {0};
    int shape[] = {4, 4};   // 矩阵的形状
    int startPoint[] = {0};
    displayMatrix(matrix, shape);   // 显示邻接矩阵

    for(int i = 0; i < N; ++i) {
        swapMatrix(vetexs, N, matrix, i);
        prim(vetexs, matrix, distance, startPoint);
        display(vetexs, distance, startPoint, N, vetexs[startPoint[i]]);
    }

    return 0;
}