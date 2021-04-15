#include <iostream>

using namespace std;

int test(int *arr, int size) {
    int min1 = 0, min2;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(arr[j] == 0) continue;
            if(arr[j] < arr[min1]){
                min2 = min1;
                min1 = j;
            }
        }
    }
}

int main() {
    return 0;
}