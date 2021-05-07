#include <iostream>

using namespace std;

#define N 4
#define INF 0x0FFFFFFF  // 设置无穷大

// 初始化distance，默认为从起点到之后每一个点的距离
void initDistance(int distance[], int matrix[][N], int start) {
    for(int i = 0; i < N; ++i) {
        distance[i] = matrix[start][i]; // distance为起点到各点的距离
    }
}

// TODO
void Prim() {

}

int main() {
    return 0;
}