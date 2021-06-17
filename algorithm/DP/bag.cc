#include <iostream>

using namespace std;

// 显示二维数组的函数
void display(int dim2[5][9], int row, int col) {
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j)
            cout << dim2[i][j] << " ";
        cout << endl;
    }
}

void display(int arr[], int size) {
    for(int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}

/*
 * 动态解决方法
 *     状态转移方程：result[i][j] = max(result[i−1][j], result[i−1][j−weight[i]]+price[i]) // j >= weight[i]
 *     参数：
 *         - weight[]：物品的重量数组
 *         - price[]：物品的价格数组
 *         - result[][]：用于存储结果的二维数组
 *         - counts：物品的个数
 *         - colume：背包的体积
*/
void dynamic_with_dim2(int weight[], int price[], int result[5][9], int counts, int volume) {
    for(int i = 1; i <= counts; ++i) {
        for(int j = 1; j <= volume; ++j) {
            if(j < weight[i]) {
                result[i][j] = result[i-1][j];
            } else {
                result[i][j] = max(result[i-1][j], result[i-1][j-weight[i]] + price[i]);
            }
        }
    }
}

void dynamic_with_dim1(int weight[], int price[], int result[], int counts, int volume) {
    for(int i = 1; i <= counts; ++i) {
        for(int j = volume; j > 0; --j) {
            result[j] = max(result[j], result[j-weight[i]] + price[i]);
            cout << result[j] << " ";
        }
    }
    cout << endl;
}


int main() {
    int counts = 4, volume = 8;
    int weight[] = {0, 2, 3, 4, 5};
    int price[] = {0, 3, 4, 5, 6};

    // 调用函数1
    int result[5][9] = {0};
    dynamic_with_dim2(weight, price, result, counts, volume);
    // 显示结果
    display(result, 5, 9);

    cout << "*******************" << endl;

    // 调用函数2
    int result1[9] = {0};
    dynamic_with_dim1(weight, price, result1, counts, volume);
    display(result1, 9);
    return 0;
}