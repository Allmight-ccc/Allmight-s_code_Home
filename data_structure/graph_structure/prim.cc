#include <iostream>

using namespace std;

#define N 4
#define INF 0xFFFFFFFF

void initDist(int c[][N], int dist[], int start) {
    for(int i = 0; i < N; ++i) {
        dist[i] = c[start][i];
    }
}

int main() {
    return 0;
}