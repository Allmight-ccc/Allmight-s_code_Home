#include <iostream>
#define N 4

using namespace std;

void display(int c[][N], int size) {
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j)
            cout << c[i][j] << " ";
        cout << endl;
    }
}


bool isEuler(char v[], int c[][N], int d[]) {
    int dg1, dg2;
    for(int i = 0; i < N; ++i) {
        dg1 = 0;
        for(int j = 0; j < N; ++j) {
            if(c[i][j] != 0) dg1++;
        }
        d[i] = dg1;
    }
    for(int i = 0; i < N; ++i) {
        dg2 = 0;
        for(int j = 0; j < N; ++j) {
            if(c[j][i] != 0) dg2++;
        }
        d[i] = d[i] + dg2;
        if(d[i] % 2 != 0) return false;
    }
    return true;
}

int main() {
    char v[] = "ABCD";
    int E[][N] = {
        {0, 1, 1, 1},
        {0, 0, 1, 1},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
    };
    int e1[][N] = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };
    int d[N] = {0};
    
    
    if(isEuler(v, E, d)) {
        display(E, N);
        cout << "上述图是欧拉图" << endl;
    } else {
        display(E, N);
        cout << "上述图是不是欧拉图" << endl;
    }

    if(isEuler(v, e1, d)) {
        display(e1, N);
        cout << "上述图是欧拉图" << endl;
    } else {
        display(e1, N);
        cout << "上述图是不是欧拉图" << endl;
    }
    return 0;
}