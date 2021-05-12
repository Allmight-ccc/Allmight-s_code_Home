#include <iostream>
#define N 4

using namespace std;

void swap(char* v, int i, int j) {
    char temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}



int main() {
    char v[] = "ABCD";
    return 0;
}