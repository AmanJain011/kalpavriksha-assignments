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

typedef struct Stack{
    Queue *queue;
} Stack;

bool push(Stack *stack, int data);
int pop(Stack *stack);
int peek(Stack *stack);
bool isEmpty(Stack *stack);
int size(Stack *stack);

void displayMenu();

int main(){
    Stack stack;
    stack.queue = (Queue *)malloc(sizeof(Queue));
    stack.queue->front = NULL;
    stack.queue->rear = NULL;
    stack.queue->size = 0;

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
                if(!push(&stack, data)){
                    printf("\n-> Stack is OverFlow\n");
                }else{
                    printf("\n-> %d pushed into the Stack\n", data);
                }
                break;
            
            case 2:
                data = pop(&stack);
                if(data == INT_MIN){
                    printf("\n-> Stack is underflow\n");
                    break;
                }
                printf("\n-> %d is successfully Popped\n", data);
                break;
            
            case 3:
                data = peek(&stack);
                if(data == INT_MIN){
                    printf("\n-> Stack is underflow\n");
                    break;
                }
                printf("\n-> %d is at the Top\n", data);
                break;

            case 4:
                if(isEmpty(&stack)){
                    printf("\n-> Stack is Empty\n");
                }else{
                    printf("\n-> Stack is not Empty\n");
                }
                break;
            
            case 5:
                printf("\n-> Size of the stack is %d\n", size(&stack));
                break;
        
            default:
                printf("\n-> Invalid Choice\n");
                break;
        }
    }

    return 0;
}

void displayMenu(){
    printf("<<-------------------------------->>\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Peek\n");
    printf("4. Is Stack Empty\n");
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

int peekQueue(Queue *queue){
    if(!queue->front){
        return INT_MIN;
    }

    return queue->front->data;
}

bool isQueueEmpty(Queue *queue){
    if(!queue->front) return true;
    return false;
}

int queueSize(Queue *queue){
    return queue->size;
}

bool push(Stack *stack, int data){
    int size = queueSize(stack->queue);
    if(!enqueue(stack->queue, data)) return false;

    if(size != 0){
        while (size--) enqueue(stack->queue, dequeue(stack->queue));
    }

    return true;
}

int pop(Stack *stack){
    return dequeue(stack->queue);
}

int peek(Stack *stack){
    return peekQueue(stack->queue);
}

bool isEmpty(Stack *stack){
    return isQueueEmpty(stack->queue);
}

int size(Stack *stack){
    return queueSize(stack->queue);
}
