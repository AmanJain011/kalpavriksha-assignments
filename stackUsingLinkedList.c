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

bool push(Stack *stack, int data);
int pop(Stack *stack);
int peek(Stack stack);
bool isEmpty(Stack stack);
int size(Stack stack);

void displayMenu();

int main(){
    Stack stack;
    stack.top = NULL;
    stack.size = 0;

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
                data = peek(stack);
                if(data == INT_MIN){
                    printf("\n-> Stack is underflow\n");
                    break;
                }
                printf("\n-> %d is at the Top\n", data);
                break;

            case 4:
                if(isEmpty(stack)){
                    printf("\n-> Stack is Empty\n");
                }else{
                    printf("\n-> Stakc is not Empty\n");
                }
                break;
            
            case 5:
                printf("\n-> Size of the stack is %d\n", size(stack));
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

bool push(Stack *stack, int data){
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

int peek(Stack stack){
    if(!stack.top){
        return INT_MIN;
    }

    return stack.top->data;
}

bool isEmpty(Stack stack){
    if(!stack.top){
        return true;
    }

    return false;
}

int size(Stack stack){
    if(!stack.top){
        return 0;
    }

    return stack.size;
}
