#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 10

typedef struct Queue{
    int array[MAX_SIZE];
    int front;
    int rear;
} Queue;

bool enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
int peek(Queue *queue);
bool isEmpty(Queue *queue);
int size(Queue *queue);

void displayMenu();

int main(){
    Queue queue;
    queue.front = -1;
    queue.rear = -1;

    int choice, data;
    while (1){
        displayMenu();

        printf("Enter Choice: ");
        if(scanf("%d", &choice) != 1){
            printf("Invalid Choice\n");
            continue;
        }

        switch (choice){
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                if(!enqueue(&queue, data)){
                    printf("\n-> Queue is OverFlow\n");
                }else{
                    printf("\n-> %d enqueued into the Queue\n", data);
                }
                break;
            
            case 2:
                data = dequeue(&queue);
                if(data == INT_MIN){
                    printf("\n-> Queue is underflow\n");
                    break;
                }
                printf("\n-> %d is successfully Dequeued\n", data);
                break;
            
            case 3:
                data = peek(&queue);
                if(data == INT_MIN){
                    printf("\n-> Queue is underflow\n");
                    break;
                }
                printf("\n-> %d is at the Front\n", data);
                break;

            case 4:
                if(isEmpty(&queue)){
                    printf("\n-> Queue is Empty\n");
                }else{
                    printf("\n-> Queue is not Empty\n");
                }
                break;
            
            case 5:
                printf("\n-> Size of the Queue is %d\n", size(&queue));
                break;
        
            default:
                printf("\n-> Invalid Choice\n");
                break;
        }
    }

    return 0;
}

void displayMenu(){
    printf("<<---------------Menu---------------->>\n");
    printf("1. Enqueue\n");
    printf("2. Dequeue\n");
    printf("3. Peek\n");
    printf("4. Is Queue Empty\n");
    printf("5. Size\n");
}

bool isFull(Queue *queue){
    return queue->front > queue->rear;
}

bool enqueue(Queue *queue, int data){
    if(queue->rear == MAX_SIZE-1) return false;

    if(queue->front == -1) {
        queue->array[++(queue->front)] = data;
        queue->rear = 0;
        return true;
    }

    queue->array[++(queue->rear)] = data;

    return true;
}

int dequeue(Queue *queue){
    if(isEmpty(queue)) return INT_MIN;

    return queue->array[(queue->front)++];
}

int peek(Queue *queue){
    if(isEmpty(queue)) return INT_MIN;
    return queue->array[queue->front];
}

bool isEmpty(Queue *queue){
    if(queue->front == -1 || queue->front > queue->rear) return true;
    return false;
}

int size(Queue *queue){
    if(isEmpty(queue)) return 0;
    return queue->rear - queue->front + 1;
}
