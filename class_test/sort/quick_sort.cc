#include <iostream>

using namespace std;

#define N 8

void display(int arr[], int size) {
    for(int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int divide(int a[], int left, int right) {
    int i = left, j = right;
    int key = a[i];
    while(i != j) {
        while(j>i && a[j]>=key) j--;
        a[i] =  a[j];
        while(i<j && a[i]<=key) i++;
        a[j] = a[i];
    }
    a[i] = key;
    display(a, N);
    return i;
}

void quickSort(int arr[], int left, int right) {
    if(left < right) {
        int i = divide(arr, left, right);
        quickSort(arr, left, i-1);
        quickSort(arr, i+1, right);
    }
}

int main() {
    int arr[N] = {5, 1, 6, 7, 2, 3, 4, 8};
    quickSort(arr, 0, 7);
    return 0;
}