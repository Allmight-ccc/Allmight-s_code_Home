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

void display_char(char p[], int size) {
    for(int i = 0; i < size; ++i)
        cout << p[i] << " ";
    cout << endl;
}

void arrange(int p[], int first, int last, int size) {
    for(int i = first; i <= last; ++i) {
        if(i != first) swap(p[first], p[i]);
        arrange(p, first+1, last, size);
        if(i != first) swap(p[first], p[i]);
    }
    if(first == last) display(p, size);
}


void insert_arr(int arranges[][4], int arr[], int& p) {
    for(int i = 0; i < 4; ++i)
        arranges[p][i] = arr[i];
    p++;
}

void to_arrange(int id[], int first, int last, int size, int arranges[][4], int& p) {
    for(int i = first; i <= last; ++i) {
        if(i != first) swap(id[first], id[i]);
        to_arrange(id, first+1, last, size, arranges, p);
        if(i != first) swap(id[first], id[i]);
    }
    if(first == last) insert_arr(arranges, id, p);
}

int main() {
    // binomia(12, 0.5);
    int a[] = {1, 2, 3, 4};
    arrange(a, 0, 3, 4);


    int p = 0;
    int arranges[200][4] = {{0}};
    int id[] = {0, 1, 2, 3};
    to_arrange(id, 0, 3, 4, arranges, p);
    for(int i = 0; i < 24; ++i) {
        for(int j = 0; j < 4; ++j) {
            cout << arranges[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}