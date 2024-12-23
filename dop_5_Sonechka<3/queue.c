#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct 
{
    int *items;
    int front;
    int rear;
    size_t size;

} queue;

void init_queue(queue* q){
    q->items = (int*)calloc(0, sizeof(int));
    q->front = 0;
    q->rear = -1;
}

void enqueue(queue* q, int x){
    q->items = (int*)realloc(q->items, sizeof(int)*(++q->rear+1));
    q->items[q->rear] = x;
}

int dequeue(queue* q){
    if (q->rear < q->front){
        printf("Очередь пуста!\n");
        exit(2);
    }

    q->front++;
    return q->items[q->front-1];
}

void free_queue(queue* q){
    free(q->items);
    q->front = 0;
    q->rear = -1;
}

int get_front(const queue q){
    if (q.rear < q.front){
        printf("Очередь пуста!\n");
        exit(2);
    }
    return q.items[q.front];
}

int get_rear(const queue q){
    if (q.rear < q.front){
        printf("Очередь пуста!\n");
        exit(2);
    }
    return q.items[q.rear];
}

int len_queue(queue q){
    return q.rear - q.front + 1;
}

