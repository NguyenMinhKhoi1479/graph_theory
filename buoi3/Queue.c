#include <stdio.h>
#define Queue_Max 500
#define data_type int

typedef struct{
    int front,rear;
    data_type data[Queue_Max];
}Queue;

void init_queue(Queue* q){
    q->front = 0;
    q->rear = 0;
}

void Enqueue(Queue *q, data_type value){
    q->data[q->rear] = value;
    q->rear++;
}

int isNullQueue(Queue q){
    return q.front == q.rear;
}

data_type Dequeue(Queue *q){
    data_type value = q->data[q->front];
    q->front++;
    if(q->front == q->rear){
        q->front = 0;
        q->rear = 0;
    }
    return value;
}

void Print_Queue(Queue q){
    if(isNullQueue(q)) return;
    for(int i = q.front ; i < q.rear ; i++){
        printf("%d ",q.data[i]);
    }
    printf("\n");
}

// int main(){
//     Queue q;
//     init_queue(&q);
//     if(isNullQueue(q)) printf("null\n");
//     Enqueue(&q,1);
//     Enqueue(&q,2);
//     Enqueue(&q,3);
//     Enqueue(&q,4);
//     Enqueue(&q,5);
//     Enqueue(&q,6);
//     Print_Queue(q);
//     Dequeue(&q);
//     Dequeue(&q);
//     Dequeue(&q);
//     Print_Queue(q);
//     return 0;
// }