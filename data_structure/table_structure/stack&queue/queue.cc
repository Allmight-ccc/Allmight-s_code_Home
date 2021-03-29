#include <iostream>

using namespace std;

#define MAXSIZE 100

struct queue {
    int *data;
    int head, tail;
};

queue* init_queue() {
    queue* q = new queue[sizeof(queue)];
    q->data = new int[MAXSIZE];
    q->head = q->tail = 0;
}

void push(queue* q, int data) {
    q->data[q->tail++] = data;
}

int pop(queue* q) {
    if(q->tail <= q->head) return -1;
    return q->data[q->head++];
}

void print_queue(queue* q) {
    for(int i = q->head; i < q->tail; ++i) {
        cout << q->data[i] << " ";
    }
    cout << endl;
}

int main() {
    int data;
    queue* q = init_queue();
    for(int i = 0; i < 5; ++i) {
        cout << ">>> ";
        cin >> data;
        push(q, data);
    }
    print_queue(q);
    


    while (true) {
        data = pop(q);
        if(data == -1) break;
        cout << "poped: " << data << endl;
    }

    return 0;
}