#include <iostream>

using namespace std;

#define MAXSIZE 100

struct stack {
    int *data;
    int top;
};

// init a stack
stack* init_stack() {
    stack *s = new stack[sizeof(stack)];
    s->data = new int[MAXSIZE];
    s->top = -1;
}

void posh(stack* s, int data) {
    if (s->top == MAXSIZE) return;

    s->data[++s->top] = data;
}

int pop(stack* s) {
    if (s->top == MAXSIZE) return;

    return s->data[s->top--];
}

void print(stack* s) {
    for (int i = 0; i < s->top; i++) {
        cout << s->data[i] << " ";
    }
    cout << endl;
}

int main() {
    return 0;
}