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


// ERROR
void combinationTest(char charArray[], int size, int index, int count, int maxCount, char result[]) {
		if (count == maxCount) {
            display_char(result, count);
            return;
        }
		
		for (int i = index; i < size; i++) {
            result[i] = charArray[i];
			combinationTest(charArray, size, i + 1, count + 1, maxCount, result);
		}
}

int main() {
<<<<<<< HEAD
    // binomia(12, 0.5);
    // int p[] = {1, 2, 3, 4};
    // arrange(p, 0, 3, 4);

    char a[] = "ABCD";
    char b[3];
    combinationTest(a, 4, 1, 3, 4, b);
=======
    binomia(12, 0.5);
    cout << "**********************" << endl;
    int p[] = {1, 2, 3, 4};
    arrange(p, 0, 3, 4);
>>>>>>> 176c58207b3977bc7f53b6fdc7d307d921f1cfcf
    return 0;
}