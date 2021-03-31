#include <iostream>

using namespace std;

int num = 0;

void hanoi(int n, int a, int b, int c) {
    if(n == 1) {
        num++;
        return;
    }
    hanoi(n-1, a, c, b);
    num++;
    hanoi(n-1, a, b, c);
}

int main() {
    return 0;
}