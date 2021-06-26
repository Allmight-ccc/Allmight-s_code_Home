#include <iostream>

using namespace std;

/*
    A: 二进制转十进制，凯撒密码加密解密
    B: 下述问题，
*/

// question of the final exam
void getMin(int *arr, int size, int *min1, int *min2) {
    while(arr[*min1] == 0) {
        (*min1)++;
        (*min2)++;
    }
    while(arr[*min2] == 0) (*min2)++;
    for(int i = *min2; i < size; ++i) {
        if(arr[i] != 0) {
            if(arr[i] < arr[*min1]) {
                *min2 = *min1;
                *min1 = i;
            } else if(arr[i] < arr[*min2]) {
                *min2 = i;
            }
        }
    }
    cout << "min: " << arr[*min1] << " sub_min: " << arr[*min2] << endl;
}

void display(int *arr, int size) {
    cout << "{ ";
    for(int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << "}" << endl;
}

void test1(int *arr, int size) {
    for(int i = 0; i < size-1; ++i) {
        int min1 = 0, min2 = 1;
        getMin(arr, size, &min1, &min2);
        arr[min1] += arr[min2];
        arr[min2] = 0;
        display(arr, size);
    }
}

int mul(int n) {
    return (n > 1) ? n*mul(n-1) : 1;
}

int add(int n) {
    return (n > 0) ? n+add(n-1) : 0;
}

int mul(int n, int m) {
    return (n > m) ? n*mul(n-1, m) : m;
}

int main() {
    // int arr[] = {7, 6, 4, 1, 3, 4, 5};
    // test1(arr, sizeof(arr)/4);
    cout << add(100) << endl;
    cout << mul(5) << endl;
    cout << mul(5, 3) << endl;
    return 0;
}