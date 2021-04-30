#include <iostream>

using namespace std;

#define N 4
#define INF 0xFFFFFFFF

void initMatrix(int mat[][N], int distance[], int start) {
    for(int i = 0; i < N; ++i) 
        distance[i] = mat[start][i];
}

int getMinDistance(int mat[][N], int flag[], int start) {
    int min = INF, k;
    
}

int main() {
    char vetexs[] = "ABCD";
    int mat[][N] = {
        {0, 2, 5, 7},
        {2, 0, 6, 3},
        {5, 6, 0, 1},
        {7, 3, 1, 0}
    };
    int distance[N] = {0};
}