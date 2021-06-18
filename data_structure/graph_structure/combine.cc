#include <iostream>
#include <cmath>
#include <stack>

using namespace std;

stack<int> s;
void D2B(int decimal) {
	while(decimal) {
		s.push(decimal % 2);
		decimal /= 2;
	}
}

void combine(char v[], int size) {
    for(int i = 0; i < pow(2, size-1); ++i) {
        int d = i;
        for(int j = 0; j < 3; ++j) {
            if(d%2==1)cout << v[j] << " ";
            else cout << " ";
            d /= 2;
        }
        cout << endl;
    }
}

int main() {
    char v[] = "ABC";
    combine(v, sizeof(v)/sizeof(char));
    return 0;
}