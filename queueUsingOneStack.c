#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;

typedef struct Stack{
    Node *top;
    int size;
} Stack;

typedef struct Queue{
    Stack *stack;
} Queue;

bool enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
int peek(Queue *queue);
bool isEmpty(Queue *queue);
int size(Queue *queue);

void displayMenu();

int main(){
    Queue queue;

    queue.stack = (Stack *)malloc(sizeof(Stack));
    queue.stack->top = NULL;
    queue.stack->size = 0;

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

bool push(Stack *stack, int data){
    if(!stack){
        stack = (Stack *)malloc(sizeof(Stack));
        stack->top = NULL;
        stack->size = 0;
    }

    Node *newNode = createNode(data);
    if (!newNode) return false;
    
    newNode->next = stack->top;
    stack->top = newNode;

    if(!stack->top->next){
        stack->size = 1;
    }else{
        stack->size += 1;
    }

    return true;
}

int pop(Stack *stack){
    if(!stack->top){
        return INT_MIN;
    }

    Node *nodeToDelete = stack->top;
    int deletedValue = nodeToDelete->data;
    stack->top = stack->top->next;

    free(nodeToDelete);

    stack->size -= 1;
    return deletedValue;
}

int peekStack(Stack *stack){
    if(!stack->top){
        return INT_MIN;
    }

    return stack->top->data;
}

bool isStackEmpty(Stack *stack){
    if(!stack->top){
        return true;
    }

    return false;
}

int stackSize(Stack *stack){
    if(!stack->top){
        return 0;
    }

    return stack->size;
}

bool enqueue(Queue *queue, int data){
    return push(queue->stack, data);
}

int dequeue(Queue *queue){
    if(isEmpty(queue)) return INT_MIN;
    if(size(queue) == 1) return pop(queue->stack);

    Node *temp = queue->stack->top;
    while (temp->next->next != NULL){
        temp = temp->next;
    }
    
    Node *nodeToDelete = temp->next;
    int deletedValue = nodeToDelete->data;
    temp->next = NULL;
    free(nodeToDelete);
    queue->stack->size -= 1;

    return deletedValue;
}

int peek(Queue *queue){
    if(isEmpty(queue)) return INT_MIN;
    if(size(queue) == 1) return peekStack(queue->stack);

    Node *temp = queue->stack->top;
    while (temp->next != NULL){
        temp = temp->next;
    }

    return temp->data;
}

bool isEmpty(Queue *queue){
    return isStackEmpty(queue->stack);
}

int size(Queue *queue){
    return stackSize(queue->stack);
}
