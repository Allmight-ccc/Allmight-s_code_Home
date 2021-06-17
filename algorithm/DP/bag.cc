#include <iostream>

using namespace std;

int max(int a, int b) {
    return (a > b) ? a : b;
}

/*
 * 动态解决方法
 * result[i][j] = max(result[i−1][j], result[i−1][j−w[i]]+v[i]) // j >= w[i]
*/
void dynamic_method(int weight[], int price[], int result[4][4], int counts, int volume) {
    for(int i = 0; i < counts; ++i) {
        for(int j = 0; j < volume; ++j) {
            if(weight[i] > j) {
                result[i][j] = result[i-1][j];
            } else {
                
            }
        }
    }
}


int main() {
    int weight[] = {0, 2, 3, 4, 5};
    int price[] = {0, 3, 4, 5, 6};

    // 初始化结果为0
    int result[5][5] = {0};
    return 0;
}