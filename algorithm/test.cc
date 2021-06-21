#include <iostream>
#include <stdio.h>
#include <cmath>

#define n 6 // 物品的个数

using namespace std;

// 显示决策向量以及背包能装的最大价值
void display_x(int x[][n], int idx, int max_val) {
    cout << "max_val = " << max_val << endl;
    cout << "x[" << idx << "][]={ ";
    for (int j = 0; j < n; j++) cout << x[idx][j] << " ";
    cout << "}" << endl;
}

// 计算重量的和
int calc_sum_weight(int x[][n], int idx, int weight[]){
	int sum_weight = 0;
    for (int j = 0; j < n; j++) if(x[idx][j] == 1) sum_weight += weight[j];
    return sum_weight;
}



/*
 * 背包问题：
 *     参数：
 *         - weight：物品的重量
 *         - val：物品的价值
 *         - c：背包的容量
 *         - x：决策向量，也就是表示那几个物品被选择
 */
void bag(int weight[], int val[], int c, int x[][n]) {
    int max_val = 0;
	int sum_weight, sum_val, max;
	for (int i = 0; i < pow(2,n); i++) {         
        sum_weight = 0;
		sum_val = 0;
		int d = i;  //将i转换为n位二进制数      
		for (int j = 0; j < n; j++){
		    if(d%2 == 1) {
			    sum_weight += weight[j];
			    sum_val += val[j];
			    x[i][j] = 1;
		    } 
		    d /= 2;     //除2	 
        }
		if(sum_val > max_val && sum_weight <= c){
		    max_val = sum_val;
		    max = i;
		}
    }

    // 显示那些物品被选择以及背包能装的最大价值是多少
    display_x(x, max, max_val);

    // 计算重量的和
	sum_weight = calc_sum_weight(x, max, weight);
    cout << "sum_weight = " << sum_weight << endl;
}
   
void knapsack(int w[],int v[],int c){
	int maxv=0;
	int sumw,sumv,max;
	for (int i = 0; i <pow(2,n); i++) {
        int d = i;                  //将转换为n位二进制数
        sumw=0;
		sumv=0;
		for (int j = 0; j < n; j++){
		    if(d%2==1){
		        sumw=sumw+w[j];
		        sumv=sumv+v[j];
		        printf("%d ",j);
		    }
		    else printf("  ");
		    d= d/2;                 //除2	 
        }
		printf("  i=%d \n",i);
		if(sumv>maxv && sumw<=c){
		    maxv=sumv;
		    max=i; 
		}
    } 
	printf("maxv=%d sumw=%d  i=%d \n",maxv,sumw, max);
}

void knapsack33(int w[],int v[],int c,int x[][n]){
	int maxv=0;
	int sumw,sumv,max;
	for (int i = 0; i <pow(2,n); i++) {         
        sumw=0;
		sumv=0;
		int d = i;   //将i转换为n位二进制数      
		for (int j = 0; j < n; j++){
		    if(d%2==1){
		        sumw=sumw+w[j];
		        sumv=sumv+v[j];
		        x[i][j]=1;
		    }	 
		    d= d/2;                 //除2	 
        }
		if(sumv>maxv && sumw<=c){
		    maxv=sumv;
		    max=i; 
		}
    } 
	printf("maxv=%d \n",maxv);
	printf("x[%d][]={ ",max);
	for (int j = 0; j < n; j++) printf("%d ",x[max][j]);
	printf("}\n");
	sumw=0;
	for (int j = 0; j < n; j++) if(x[max][j]==1) sumw=sumw+w[j];
	printf("sumw=%d \n",sumw);
}

int main() {
	int w[]={3, 4, 6, 7, 8, 9};    //物品重量
	int v[]={13, 9, 9, 15, 17, 19};  //物品价值
	int c=16;  // 背包容量
	int x[64][n]={0};
	knapsack(w,v,c);
    knapsack33(w,v,c, x);
    bag(w,v,c,x);
    return 0;
}
