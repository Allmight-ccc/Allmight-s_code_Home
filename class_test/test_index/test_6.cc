#include <iostream>

using namespace std;

// 获取最小值和次小值的索引
void getMin(int *arr, int size, int& min1, int& min2) {
    while(arr[min1] == 0) { min1++; min2++; }
    while(arr[min2] == 0) min2++;
    for(int i = min2; i < size; ++i) {
        if(arr[i] != 0) {   // 当arr[i]不为零的时候交换最小值和次小值的索引
            if(arr[i] < arr[min1]) {    // 此时让min2为min1，让min1为i
                min2 = min1;
                min1 = i;
            } else if(arr[i] < arr[min2]) {
                min2 = i;   // 让min2为i，表示次小值
            }
        }
    }
    cout << "min: " << arr[min1] << " sub_min: " << arr[min2] << endl;
}

// 打印数组
void display(int *arr, int size) {
    cout << "{ ";
    for(int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << "}" << endl;
}

void test1(int *arr, int size) {
    for(int i = 0; i < size-1; ++i) {
        int min1 = 0, min2 = 1; // 初始化min1和min2的值
        getMin(arr, size, min1, min2);  // 令min1和min2分别表示最小值和次小值的索引
        arr[min1] += arr[min2]; // 令最小值为最小值和次小值二者之和
        arr[min2] = 0;  // 令次小值为0
        display(arr, size); // 打印数组
    }
}

int main() {
    int arr[] = {7, 6, 4, 1, 3, 4, 5};
    test1(arr, sizeof(arr)/4);
    return 0;
}