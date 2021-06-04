#include <iostream>

using namespace std;

<<<<<<< HEAD
#define N 4
#define INF 0x0FFFFFFF

void display(char vetexts[], int distance[], int startPoint[], int size, char word) {
    cout << "从" << word << "点到各点的距离为：";
    for(int i = 0; i < N; ++i) {
        if(i == N-1) { 
            cout << distance[i] << endl;
            break;
        }
        cout << distance[i] << "==>";
=======
#define n 4
#define INF 0xFFFFFFF
/*
char V[] ——顶点数组
int c[][n] ——邻接矩阵
int dist[] ——数组,dist[i]是start到顶点i的最短路径 
int u[] ——dist[i]的起点,Prim算法中dist[i]的起点是变动的 
*/
void swap(char V[], int Mat[][n], int start)
{
    int temp, i;
    char temp2;
    temp2 = V[0];
    V[0] = V[start];
    V[start] = temp2;
    for (i = 0; i < n; i++)
    {
        temp = Mat[0][i];
        Mat[0][i] = Mat[start][i];
        Mat[start][i] = temp;
    }
    for (i = 0; i < n; i++)
    {
        temp = Mat[i][0];
        Mat[i][0] = Mat[i][start];
        Mat[i][start] = temp;
    }
}

void intDist(int dist[], int u[], char V[], int c[][n])
{
    cout << "1. init dist[],dist[i]=c[start][i]" << endl;
    for (int i = 1; i < n; i++)
    {
        dist[i] = c[0][i];
        u[i] = 0;
        cout << "Dist[" << i << "]=" << dist[i] << " u[" << i << "]=" << u[i] << ";" << endl;
>>>>>>> e65a7d6b4c7ef7d84d4ddf0710fa3f3851e243b9
    }
    cout << endl;
}

<<<<<<< HEAD
void displayMatrix(int matrix[][N], int shape[2]) {
    for(int i = 0; i < shape[0]; ++i) {
        for(int j = 0; j < shape[1]; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void swapMatrix(char vetexs[], int VetexSize, int mat[][N], int start) {
    swap(vetexs[0], vetexs[start]);
    for(int i = 0; i < VetexSize; ++i) swap(mat[i][start], mat[i][0]);
    for(int i = 0; i < VetexSize; ++i) swap(mat[start][i], mat[0][i]);
}

void initDistance(int distance[], int matrix[][N], int startPoint[]) {
    for(int i = 0; i < N; ++i) {
        startPoint[i] = 0;
        distance[i] = matrix[0][i];
    }
}

int getMinDistance(int distance[]) {
    int min = INF, min_index;
    for(int i = 0; i < N; ++i) {
        if(distance[i] < min) {
            min = distance[i];
            min_index = i;
        }
    }
    return min_index;
}

int Min(int a, int b) {
    return a>b ? b : a;
}

void updateDistance(int matrix[][N], int distance[], int startPoint[], int min_index) {
    for(int i = 0; i < N; ++i) {
        if(distance[min_index] < distance[i]) {
            distance[i] = matrix[min_index][i];
            startPoint[i] = min_index;
        }
    }
}

void prim(char vetexs[], int matrix[][N], int distance[], int startPoint[]) {
    initDistance(distance, matrix, startPoint);
    for(int i = 0; i < N-1; ++i) {
        int min_index = getMinDistance(distance);
        updateDistance(matrix, distance, startPoint, min_index);
    }
}

int main() {
    char vetexs[] = "ABCD";
    int matrix[][N] = {
        {0, 2, 5, 7},
        {2, 0, 8, 3},
        {5, 8, 0, 1},
        {7, 3, 1, 0}
    };
    int distance[N] = {0};
    int shape[] = {4, 4};   // 矩阵的形状
    int startPoint[] = {0};
    displayMatrix(matrix, shape);   // 显示邻接矩阵

    for(int i = 0; i < N; ++i) {
        swapMatrix(vetexs, N, matrix, i);
        prim(vetexs, matrix, distance, startPoint);
        display(vetexs, distance, startPoint, N, vetexs[startPoint[i]]);
    }

    return 0;
=======
int getMinDist(int dist[])
{
    int min = INF;
    int k;
    for (int i = 1; i < n; i++)
    {
        if (dist[i] < min && dist[i] != 0)
        {
            min = dist[i];
            k = i;
        }
    }
    cout << "2. 从Dist中,找出一条圈中最小(!=0)边的终点k\n"
         << endl;
    return k;
}

void updateDist(int dist[], int u[], int c[][n], int k)
{
    cout << "3. 比较dist[i]>c[k][i],更新dist[i]" << endl;
    for (int i = 1; i < n; i++)
    {
        if (dist[i] > c[k][i])
        {
            dist[i] = c[k][i];
            u[i] = k;
        }
        cout << "Dist[" << i << "]=" << dist[i] << ","
             << "u[" << i << "]=" << u[i] << ";";
    }
    cout << endl;
}

void Prim(int dist[], int u[], char V[], int c[][n])
{
    intDist(dist, u, V, c);
    for (int i = 0; i < n - 1; i++)
    {
        int k = getMinDist(dist);
        printf("k=%d dist[%d]=%d \n%c -> %c\n", k, k, dist[k], V[u[k]], V[k]);
        updateDist(dist, u, c, k);
    }
}

void displayMat(int Mat[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << Mat[i][j];
        cout << endl;
    }
}

main()
{
    int dist[n] = {0};
    int u[n] = {0};
    char V[] = "ABCD";
    int c[][n] =
        {{0, 2, 5, 7},
         {2, 0, 6, 3},
         {5, 6, 0, 1},
         {7, 3, 1, 0}};
    int start = 0;
    cout << "————————Prim:c,start=0————————" << endl;
    cout << V[0] << " " << V[1] << " " << V[2] << " " << V[3] << endl;
    displayMat(c);
    Prim(dist, u, V, c);

    cout << "————————Prim:c,start=1————————" << endl;
    start = 1;
    swap(V, c, start);
    cout << V[0] << " " << V[1] << " " << V[2] << " " << V[3] << endl;
    displayMat(c);
    Prim(dist, u, V, c);

    cout << "————————Prim:c,start=2————————" << endl;
    start = 2;
    swap(V, c, start);
    cout << V[0] << " " << V[1] << " " << V[2] << " " << V[3] << endl;
    displayMat(c);
    Prim(dist, u, V, c);

    cout << "————————Prim:c,start=3————————" << endl;
    start = 3;
    swap(V, c, start);
    cout << V[0] << " " << V[1] << " " << V[2] << " " << V[3] << endl;
    displayMat(c);
    Prim(dist, u, V, c);
>>>>>>> e65a7d6b4c7ef7d84d4ddf0710fa3f3851e243b9
}