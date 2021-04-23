#include <iostream>

using namespace std;

void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

void swapVetex(int *vetexs, int VetexSize, int **mat, int start) {
    swap(vetexs[0], vetexs[start]);

    for(int i = 0; i < VetexSize; ++i)
        swap(mat[start][i], mat[0][i]);

    for(int i = 0; i < VetexSize; ++i)
        swap(mat[i][start], mat[i][0]);
}

void display(int *mat[], int rows, int cols) {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    char X[4] = {'A', 'B', 'C', 'D'};
    int mat[][4] = {
        {0, 2, 5, 7},
        {2, 0, 6, 3},
        {5, 6, 0, 1},
        {7, 3, 1, 0}};
        // display(mat, 4, 4);
    return 0;
}