#include <iostream>

using namespace std;

void print_array(int* arr, int size) {
    for(int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void print_array(int* arr, int size, int* index) {
    for(int i = 0; i < size; ++i) {
        cout << arr[index[i]] << " ";
    }
    cout << endl;
}

int* copy_array(int* arr, int size) {
    int* new_arr = new int[size];
    for(int i = 0; i < size; ++i) {
        new_arr[i] = arr[i];
    }
    return new_arr;
}

int index[11] = {1};
void sort(int* arr, int size) {
    int min = 0;
    int *new_arr = copy_array(arr, size);
    for(int i = 0; i < size; i++) {
        min = index[i]-1;
        for(int j = 0; j < size; j++) {
            if(new_arr[j] == 0) continue;
            if(new_arr[j] < new_arr[min]) min = j;
        }
        index[i] = min;
        new_arr[min] = 0;
    }
}

int main() {
    int arr[] = {54, 34, 21, 213, 100, 43, 333, 249, 1, 43, -132, 67};
    sort(arr, sizeof(arr)/4);
    print_array(arr, sizeof(arr)/4);
    print_array(arr, sizeof(arr)/4, index);
    return 0;
}