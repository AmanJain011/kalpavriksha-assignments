#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 10

typedef struct Stack{
    int array[MAX_SIZE];
    int top;
} Stack;

bool push(Stack *stack, int data);
int pop(Stack *stack);
int peek(Stack stack);
bool isEmpty(Stack stack);
int size(Stack stack);

void displayMenu();

int main(){
    Stack stack;
    stack.top = -1;

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
    printf("<<-------------------------------->>\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Peek\n");
    printf("4. Is Stack Empty\n");
    printf("5. Size\n");
}

bool push(Stack *stack, int data){
    if(stack->top == MAX_SIZE-1) return false;

    stack->array[++(stack->top)] = data;
    return true;
}

int pop(Stack *stack){
    if(stack->top == -1){
        return INT_MIN;
    }

    int deletedValue = stack->array[stack->top--];
    return deletedValue;
}

int peek(Stack stack){
    if(stack.top == -1){
        return INT_MIN;
    }

    return stack.array[stack.top];
}

bool isStackEmpty(Stack *stack){
    if(stack->top == -1){
        return true;
    }

    return false;
}

int size(Stack stack){
    return stack.top + 1;
}
