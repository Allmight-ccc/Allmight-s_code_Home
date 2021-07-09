#include <iostream>

using namespace std;

/*
    A: 二进制转十进制，凯撒密码加密解密
    B: 下述问题，
*/

// question of the final exam
void getMin(int *arr, int size, int *min1, int *min2) {
    while(arr[*min1] == 0) {
        (*min1)++;
        (*min2)++;
    }
    while(arr[*min2] == 0) (*min2)++;
    for(int i = *min2; i < size; ++i) {
        if(arr[i] != 0) {
            if(arr[i] < arr[*min1]) {
                *min2 = *min1;
                *min1 = i;
            } else if(arr[i] < arr[*min2]) {
                *min2 = i;
            }
        }
    }
    cout << "min: " << arr[*min1] << " sub_min: " << arr[*min2] << endl;
}

void display(int *arr, int size) {
    cout << "{ ";
    for(int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << "}" << endl;
}

void test1(int *arr, int size) {
    for(int i = 0; i < size-1; ++i) {
        int min1 = 0, min2 = 1;
        getMin(arr, size, &min1, &min2);
        arr[min1] += arr[min2];
        arr[min2] = 0;
        display(arr, size);
    }
}

int mul(int n) {
    return (n > 1) ? n*mul(n-1) : 1;
}

int add(int n) {
    return (n > 0) ? n+add(n-1) : 0;
}

int mul(int n, int m) {
    return (n > m) ? n*mul(n-1, m) : m;
}



void swap(int a[],int i,int j)
{
	int temp=a[i];
	a[i]=a[j];
	a[j]=temp;
}

int getmin(int a[],int n,int i)
{
	int min=i;
	for(int j=i;j<n;j++)
	if(a[j]<a[min])
	min=j;
	return min;
}

void sort(int a[],int n)
{
	for(int i=0;i<n-1;i++)
	{
		int min=getmin(a,n,i);
		swap(a,i,min);
	}	
}



void GetMin(int a[],int len,int * min1,int * min2) {
	while(a[*min1]==0)(*min1)++,(*min2)++;
	while(a[*min2]==0)(*min2)++;
	for(int i=*min2;i<len;i++)
	if(a[i]!=0) {
		if(a[i]<a[*min1]) {
			*min2=*min1;
			*min1=i;
		} else if(a[i]<a[*min2])
			*min2=i;
	}
}

//2.再定义一个循环调用求最小值和次小值
void GetSum(int a[],int len)
{
	int min1,min2;
	for(int i=0;i<len;i++) {
    min1=0,min2=1;
	GetMin(a,len,&min1,&min2);
	a[min1]=a[min1]+a[min2];
	a[min2]=0;
    }
}


int main() {
    // int arr[] = {7, 6, 4, 1, 3, 4, 5};
    // test1(arr, sizeof(arr)/4);
    cout << add(100) << endl;
    cout << mul(5) << endl;
    cout << mul(5, 3) << endl;
    return 0;
}