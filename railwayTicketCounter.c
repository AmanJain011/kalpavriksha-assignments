#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum PassangerType{
    VIP,
    SENIOR_CITIZEN,
    GENERAL
} PassangerType;

typedef struct Passanger{
    int id;
    PassangerType type;
    char name[50];
} Passanger;

typedef struct Node{
    Passanger passanger;
    struct Node *next;
} Node;

typedef struct Queue{
    Node *front;
    Node *rear;
    int size;
} Queue;

void displayPassanger(Passanger passanger){
    char type[3][20] = {"VIP", "SENIOR_CITIZEN", "GENERAL"};
    printf("ID %d, Name %s, Type %s\n", passanger.id, passanger.name, type[passanger.type]);
}

Node* createNode(Passanger passanger){
    Node *node = (Node *)malloc(sizeof(Node));
    if(!node) return NULL;

    node->passanger = passanger;
    node->next = NULL;

    return node;
}

bool enqueue(Queue *queue, Passanger passanger){
    Node *newNode = createNode(passanger);
    if(!newNode) return false;

    if(!queue->front){
        queue->front = newNode;
        queue->size = 1;
    }else{
        queue->rear->next = newNode;
        queue->size += 1;
    }

    queue->rear = newNode;

    return true;
}

Passanger dequeue(Queue *queue){
    Passanger p;
    p.id = -1;
    if(!queue->front) p;

    Node *nodeToDelete = queue->front;
    Passanger deletedPassanger = nodeToDelete->passanger;
    queue->front = queue->front->next;
    queue->size -= 1;

    free(nodeToDelete);
    return deletedPassanger;
}

bool isEmpty(Queue queue){
    if(queue.size == 0) return true;
    return false;
}

void printQueue(Queue queue){
    Node *current = queue.front;
    while (current != NULL){
        displayPassanger(current->passanger);
        current = current->next;
    }
}

PassangerType getPassangerTypeFromString(char *str) {
    if (strcmp(str, "VIP") == 0) return VIP;
    if (strcmp(str, "SENIOR_CITIZEN") == 0) return SENIOR_CITIZEN;
    if (strcmp(str, "GENERAL") == 0) return GENERAL;
    return -1;
}

int main(){
    Queue queues[3];

    queues[0].front = NULL;
    queues[0].rear = NULL;
    queues[0].size = 0;

    queues[1].front = NULL;
    queues[1].rear = NULL;
    queues[1].size = 0;

    queues[2].front = NULL;
    queues[2].rear = NULL;
    queues[2].size = 0;

    int operations, choice;
    scanf("%d", &operations);

    while (operations--){
        scanf("%d", &choice);
        Passanger passanger;
        char type[20];

        switch (choice){
            case 1:
                scanf("%d %s %s", &passanger.id, type, passanger.name);
                passanger.type = getPassangerTypeFromString(type);
                enqueue(&queues[passanger.type], passanger);
                break;
            
            case 2:
                for(int i=0; i<3; i++){
                    if(isEmpty(queues[i])) continue;
                    passanger = dequeue(&queues[i]);
                    break;
                }
                printf("Serving Passenger: ");
                displayPassanger(passanger);
                printf("\n");
                break;

            case 3:
                printf("Waiting Passengers: \n");
                for(int i=0; i<3; i++){
                    if(isEmpty(queues[i])) continue;
                    printQueue(queues[i]);
                }
                printf("\n");
                break;
            
            default:
                break;
        }
    }

    return 0;
}
