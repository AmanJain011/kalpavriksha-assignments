#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;

typedef struct Queue{
    Node *front;
    Node *rear;
    int size;
} Queue;

bool enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
int peek(Queue *queue);
bool isEmpty(Queue *queue);
int size(Queue *queue);

void displayMenu();

int main(){
    Queue queue;
    queue.front = NULL;
    queue.rear = NULL;
    queue.size = 0;

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

Node* createNode(int data){
    Node *node = (Node *)malloc(sizeof(Node));
    if(!node) return NULL;

    node->data = data;
    node->next = NULL;

    return node;
}

bool enqueue(Queue *queue, int data){
    Node *newNode = createNode(data);
    if(!newNode) return false;

    if(!queue->rear){
        queue->rear = newNode;
        queue->front = newNode;
        queue->size = 1;

        return true;
    }

    queue->rear->next = newNode;
    queue->rear = newNode;
    queue->size += 1;

    return true;
}

int dequeue(Queue *queue){
    if(!queue->front){
        return INT_MIN;
    }

    Node *nodeToDelete = queue->front;
    int deletedValue = nodeToDelete->data;
    queue->front = queue->front->next;

    free(nodeToDelete);
    queue->size -= 1;

    if(!queue->size){
        free(queue->rear);
        queue->rear = NULL;
    }
    
    return deletedValue;
}

int peek(Queue *queue){
    if(!queue->front){
        return INT_MIN;
    }

    return queue->front->data;
}

bool isEmpty(Queue *queue){
    if(!queue->front) return true;
    return false;
}

int size(Queue *queue){
    return queue->size;
}
