#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct _Queue{
    int front,rear;
    int items[MAX+1];
}Queue;

bool isEmpty(Queue *queue);
bool isFull(Queue *queue);
void enqueue(Queue *queue, int item);
int dequeue(Queue *queue);
void printItems(Queue *queue);

int main(){
    Queue queue;
    queue.rear=0;
    queue.front=0;

    enqueue(&queue, 1);
	enqueue(&queue, 3);
	enqueue(&queue, 2);
	printItems(&queue);

	dequeue(&queue);
	enqueue(&queue, 4);
	printItems(&queue);

	enqueue(&queue, 10);
	printItems(&queue);

	// Remove the queue
	return 0;
}

bool isEmpty(Queue *queue){
    return queue->rear==queue->front;
}

bool isFull(Queue *queue){
    return queue->front==(queue->rear+1)%(MAX+1);
}

void enqueue(Queue *queue, int item){
    if(isFull(queue)){
        printf("FULL\n");
        return;
    }
    queue->items[queue->rear]=item;
    queue->rear=(queue->rear+1)%(MAX+1);
}

int dequeue(Queue *queue){
    if(isEmpty(queue)){
        printf("EMPTY\n");
    }
    int n=queue->front;
    queue->front=(queue->front+1)%(MAX+1);
    return queue->items[n];
}

void printItems(Queue *queue){
    if(isEmpty(queue)){
        printf("EMPTY\n");
        return;
    }
    if(queue->rear>queue->front){
        for(int i=queue->rear-1;i>=queue->front;i--){
            printf("%d ",queue->items[i]);
        }
        printf("\n");
        return;
    }
    else{
        for(int i=queue->rear;i>=0;i--){
            printf("%d ",queue->items[i]);
        }
        for(int i=MAX;i>=queue->front;i--){
            printf("%d ",queue->items[i]);
        }
        printf("\n");
    }
}