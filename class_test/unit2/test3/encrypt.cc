#include <iostream>
#include <queue>

using namespace std;

// 凯撒密码，使用队列进行临时存储
queue<int> q;  // 用于存储加密后的字符 

// 加密函数 
void encrypt(char* str, int size) {
	for(int i = 0; i < size; ++i) {
		if(str[i] >= 97 && str[i] <= 122)
			q.push((char)(((int)str[i]-97 + 3) % 26 + 97));
		if(str[i] >= 65 && str[i] <= 90)
			q.push((char)(((int)str[i]-65 + 3) % 26 + 65));
	}
}

// 解密函数 
void decrypt(char* str, int size) {
	for(int i = 0; i < size; ++i) { 
		if(str[i] >= 97 && str[i] <= 122)
			q.push((char)(((int)str[i]-97 - 3) % 26 + 97));
		if(str[i] >= 65 && str[i] <= 90) 
			q.push((char)(((int)str[i]-65 - 3) % 26 + 65));
	}
}

// 打印数组中的元素 
void print_array(char* str, int size) {
	for(int i = 0; i < size; ++i) {
		cout << str[i];
	}
	cout << endl;
}

// 打印队列中的元素，每次打印清空队列 
void print_queue(queue<int>& q) {
	while(!q.empty()) {
		cout << (char)q.front();  // 打印数组的第一个元素 
		q.pop();
	}
	cout << endl;
}

int main() {
	char str1[10] = {'H', 'e', 'l', 'l', 'o', 'W', 'o', 'r', 'l', 'd'};
	cout << "加密前：";
	print_array(str1, 10);
	
	encrypt(str1, 10);
	cout << "加密后：";
	print_queue(q);

    // 加密后的helloworld 
	char str2[10] = {'K', 'h', 'o', 'o', 'r', 'Z', 'r', 'u', 'o', 'g'};
	cout << "解密前：";
    print_array(str2, 10);

    decrypt(str2, 10);
    cout << "解密后：";
	print_queue(q);

	return 0;
}