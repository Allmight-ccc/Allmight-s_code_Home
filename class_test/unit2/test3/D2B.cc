#include <iostream>
#include <stack>

using namespace std;

// 使用栈来存储10进制数转换成的2进制数
stack<int> s;  // 用于存储二进制结果栈 
void D2B(int decimal) {  // 十进制转二进制函数 
	while(decimal) {     // 当ff==0的时候结束循环 
		s.push(decimal % 2);  // 将ff%2的结果压入栈中 
		decimal /= 2;	 // 更新原有十进制数 
	}
}

// 打印栈函数 
void print_stack(stack<int>& s) { // 传入一个栈引用 
	while(!s.empty()) {   // 当栈不为空的时候循环 
		cout << s.top();  // 输出栈顶元素 
	    s.pop(); 		  // 弹出栈顶元素 
	}
	cout << endl; 
}

int main() {
	D2B(15);
    cout << "15的二进制代码: ";
	print_stack(s);
    return 0;
}