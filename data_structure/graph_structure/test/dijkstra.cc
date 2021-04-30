#include <iostream>

using namespace std;

#define N 4
#define INF 0xFFFFFFFF

void initDist(int c[][N], int dist[], int start) {
    for(int i = 0; i < N; ++i) {
        dist[i] = c[start][i];
    }
}

int getMinDist(int c[][N], int flag[], int dist[], int start) {
    int min = INF, k;
}

int getMin(int a, int b) {
    return a < b ? a : b;
}

void updateDist(int c[][N], int flag[], int dist[], int k, int start) {
    for(int i = 0; i < N; ++i) {
        int min = getMin(dist[k] + c[k][i], c[start][i]);
        
    }
}

void dijkstra(char V[], int c[][N], int dist[], int start) {
    initDist(c, dist, start);
    int flag[N] = {0};
    flag[start] = 1;
    for(int i = 0; i < N-1; ++i) {
        int k = getMinDist(c, flag, dist, start);
        flag[k] = 1;
        updateDist(c, flag, dist, k, start);
    }
}

int main() {
    return 0;
}