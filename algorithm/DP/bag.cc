#include <iostream>
#include <cmath>

using namespace std;

// 背包的容量，实际为8，第一个元素为0
#define N 9

int max(int a, int b) {
    return (a > b) ? a : b;
}

/*
 * 动态规划解决方法：
 *     状态转移方程：result[i][j] = max(result[i−1][j], result[i−1][j−weight[i]]+price[i]) // j >= weight[i]
 * 
 *     参数：
 *         - weight[]：物品的重量数组
 *         - price[]：物品的价格数组
 *         - result[][]：用于存储结果的二维数组
 *         - counts：物品的个数
 *         - colume：背包的体积
*/
void dynamic_with_dim2(int weight[], int price[], int result[5][9], int counts, int volume) {
    for(int i = 1; i <= counts; ++i)
        for(int j = 1; j <= volume; ++j)
            result[i][j] = (j < weight[i]) ? result[i-1][j] : max(result[i-1][j], result[i-1][j-weight[i]] + price[i]);
}

/*
 * 优化版动态规划解决方法：
 *     
 *     优化内容：
 *         使用动态规划方法的存储数组是一个二维数组，大小为M*N，当背包容量和物品数量足够大时，会占用很大的空间。
 *       在上一个方法中，我们发现result[i][j]的取值实际上只与result[i-1][j]有关，这为我们将二维数组简化成一个
 *       一维数组提供了可能，简化后的数组的空间为n，也就是背包的容积大小。
 * 
 *     状态转移方程：result[j] = max(result[j], result[j-weight[i]] + price[i])
 *     
 *     参数：同上
*/
void dynamic_with_dim1(int weight[], int price[], int result[], int counts, int volume) {
    for(int i = 1; i <= counts; ++i)
        for(int j = volume; j > 0; --j)
            result[j] = (j < weight[i]) ? result[j] : max(result[j], result[j-weight[i]] + price[i]);
}

/*
 *  最终版优化算法：
 *      优化内容：优化了第二层for循环的循环次数，并且减少了一句判断语句
 *      
 *      状态转移方程：result[j] = max(result[j], result[j-weight[i]] + price[i])
 *      
 *      参数：同上
*/
void dynamic_with_dim1_final(int weight[], int price[], int result[], int counts, int volume) {
    for(int i = 1; i <= counts; ++i)
        for(int j = volume; j >= weight[i]; --j)
            result[j] = max(result[j], result[j-weight[i]] + price[i]);
}

// 显示二维数组的函数
void display(int arr[][N], int row, int col) {
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j)
            cout << arr[i][j] << " ";
        cout << endl;
    }
}

// 显示一位数组的函数
void display(int arr[], int size) {
    for(int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int counts = 4, volume = 8;     // 物品的个数和背包的容量
    int weight[] = {0, 2, 3, 4, 5}; // 物品的重量
    int price[] = {0, 3, 4, 5, 6};  // 物品的价值

    // 调用函数1
    int result1[5][9] = {0};
    dynamic_with_dim2(weight, price, result1, counts, volume);
    display(result1, 5, 9);
    cout << "该背包可装物品的最大价值为：" << result1[4][8] << endl;

    // cout << "*******************" << endl;

    // 调用函数2
    // int result1[9] = {0};
    // dynamic_with_dim1(weight, price, result1, counts, volume);
    // display(result1, 9);
    return 0;
}