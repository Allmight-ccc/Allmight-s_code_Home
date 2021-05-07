#include <iostream>

using namespace std;

#define N 4
#define INF 0x0FFFFFFF  // 设置无穷大

// 显示数组函数
void display(int arr[], int size, char word) {
    cout << "从" << word << "点到各点的距离为：";
    for(int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 初始化distance，默认为从起点到之后每一个点的距离
void initDistance(int distance[], int matrix[][N], int start) {
    for(int i = 0; i < N; ++i) {
        distance[i] = matrix[start][i];
    }
}

// 获取distance中最小的一个距离，返回这个距离在数组中的索引
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

// 更新距离，使距离最小
void updateDistance(int matrix[][N], int distance[], bool flag[], int index, int start) {
    for(int i = 0; i < N; ++i) {
        int min = Min(distance[index] + matrix[index][i], matrix[start][i]);    // 返回两者小的那一个
        if(min < distance[i] && flag[i] == false) { // 当min小于原距离且该点没被访问过时，进行操作
            distance[i] = min;  // 更新距离
        }
    }
}

// 算法主体
void dijkstra(char vetexs[], int matrix[][N], int distance[], int start) {
    initDistance(distance, matrix, start);  // 初始化距离
    bool flag[N] = {false};
    flag[start] = true;
    for(int i = 0; i < N-1; ++i) {  // 对剩余的N-1个点进行操作
        int min_index = getMinDistance(distance, flag, start);  //  获取最小距离的索引
        flag[min_index] = true; // 标记以访问
        updateDistance(matrix, distance, flag, min_index, start);   // 更新距离
    }
}

// 显示矩阵函数, 传入矩阵和矩阵形状
void displayMatrix(int matrix[][N], int shape[2]) {
    for(int i = 0; i < shape[0]; ++i) { // 遍历行
        for(int j = 0; j < shape[1]; ++j) { // 遍历列
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    char vetexs[] = "ABCD";
    int matrix[][N] = {
        {0, 2, 5, 7},
        {2, 0, 6, 3},
        {5, 6, 0, 1},
        {7, 3, 1, 0}
    };
    int distance[N] = {0};
    int shape[] = {4, 4};
    displayMatrix(matrix, shape);

    // 起点为A的最短路径
    dijkstra(vetexs, matrix, distance, 0);
    display(distance, N, 'A');

    // 起点为B的最短路径
    dijkstra(vetexs, matrix, distance, 1);
    display(distance, N, 'B');

    // 起点为C的最短路径
    dijkstra(vetexs, matrix, distance, 2);
    display(distance, N, 'C');

    // 起点为D的最短路径
    dijkstra(vetexs, matrix, distance, 3);
    display(distance, N, 'D');
}