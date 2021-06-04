#include <iostream>
#include <cmath>

using namespace std;

// 概率题
double C(int n, int k) {
    return (k == 0 || k == n) ? 1 : (n - k + 1) * C(n, k-1) / k;
}

void binomia(int n, double p) {
    double sum = 0;
    double Xk = 0;
    for(int i = 0; i <= n; ++i) {
        Xk = C(n, i) * pow(p, i) * pow(1-p, n-i);
        sum += Xk;
        cout << "命中" << i << "个的概率是：" << Xk << endl;
    }
    cout << "sum = " << sum << endl;
}

// 全排列题
void swap(int& a, int& b) {
    int temp = a;
    a = b; 
    b = temp;
}

void display(int p[], int size) {
    for(int i = 0; i < size; ++i)
        cout << p[i] << " ";
    cout << endl;
}
// TODO
void arrange(int p[], int first, int last, int size) {
    for(int i = first; i <= last; ++i) {
        if(i != first) swap(p[first], p[i]); // 依次取每一个元素为前一个元素
        display(p, size);
        if(i != first) swap(p[first], p[i]);
    }
}

int main() {
    binomia(12, 0.5);
    int p[] = {1, 2, 3, 4};
    arrange(p, 0, 3, 4);
    return 0;
}