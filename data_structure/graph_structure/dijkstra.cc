#include <iostream>

using namespace std;

#define N 4
#define INF 0x0FFFFFFF

void display(int arr[], int size, char word) {
    cout << "从" << word << "点到各点的距离为：";
    for(int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
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

void initDistance(int distance[], int matrix[][N], int start) {
    for(int i = 0; i < N; ++i) {
        distance[i] = matrix[start][i];
    }
}

int getMinDistance(int distance[], bool flag[], int start) {
    int min = INF, min_index;
    for(int i = 0; i < N; ++i) {
        if(flag[i] == false && distance[i] < min) {
            min = distance[i];
            min_index = i;
        }
    }
    return min_index;
}

int Min(int a, int b) {
    return a>b ? b : a;
}

void updateDistance(int matrix[][N], int distance[], bool flag[], int index, int start) {
    for(int i = 0; i < N; ++i) {
        int min = Min(distance[index] + matrix[index][i], matrix[start][i]);
        if(min < distance[i] && flag[i] == false) {
            distance[i] = min;
        }
    }
}

void dijkstra(char vetexs[], int matrix[][N], int distance[], int start) {
    initDistance(distance, matrix, start);
    bool flag[N] = {false};
    flag[start] = true;
    for(int i = 0; i < N-1; ++i) {
        int min_index = getMinDistance(distance, flag, start);
        flag[min_index] = true;
        updateDistance(matrix, distance, flag, min_index, start);
    }
}

int main() {
    return 0;
}