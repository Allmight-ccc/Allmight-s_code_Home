#include <iostream>

using namespace std;

#define MAXSIZE 100

struct queue {
    int *data;
    int size;
};

queue* init_queue() {
    queue* q = new queue[sizeof(queue)];
    q->data = new int[MAXSIZE];
    q->size = 0;
}

int main() {
    return 0;
}