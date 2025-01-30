#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int id;
    char *severityLevel;
    struct Node *next;
} Node;

Node* createNode(int id, char *severityLevel){
    Node *node = (Node *)malloc(sizeof(Node));
    node->severityLevel = (char *)malloc(sizeof(char)*10);

    node->id = id;
    node->severityLevel = severityLevel;
    node->next = NULL;
    return node;
}

void insertNode(Node **head, int id, char *severityLevel){
    Node* newNode = createNode(id, severityLevel);

    if(*head == NULL){
        *head = newNode;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL){
        temp = temp->next;
    }

    temp->next = newNode;
}

void printList(Node *head){
    Node *temp = head;
    while (temp != NULL){
        printf("{%d %s} -> ", temp->id, temp->severityLevel);
        temp = temp->next;
    }
    printf("NULL\n");
}

int getIndex(char* severityLevel, char* levels[]){
    for(int i=0; i<3; i++){
        if(!strcmp(severityLevel, levels[i])){
            return i;
        }
    }
    return -1;
}

Node *getMid(Node *head){
    if(head == NULL || head->next == NULL) return head;

    Node *slow = head;
    Node *fast = head;

    while (fast->next != NULL && fast->next->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

Node* mergeSortedList(Node *l1, Node *l2, char* levels[]){
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;

    Node *c1 = l1;
    Node *c2 = l2;
    Node *dummy = createNode(-1, "dummy");
    Node *prev = dummy;

    while (c1 != NULL && c2 != NULL){
        if(getIndex(c1->severityLevel, levels) <= getIndex(c2->severityLevel, levels)){
            prev->next = c1;
            c1 = c1->next;
        }else{
            prev->next = c2;
            c2 = c2->next;
        }

        prev = prev->next;
    }

    prev->next = (c1 != NULL ? c1 : c2);
    return dummy->next;
}

Node* mergeSort(Node *head, char* levels[]){
    if(head == NULL || head->next == NULL) return head;

    Node *midNode = getMid(head);
    Node *newHead = midNode->next;
    midNode->next = NULL;

    Node* l1 = mergeSort(head, levels);
    Node* l2 = mergeSort(newHead, levels);

    return mergeSortedList(l1, l2, levels);
}


int isIdPresent(Node* head, int id){
    Node *temp = head;
    while (temp != NULL){
        if(temp->id == id){
            printf("Id Already Present\n");
            return 1;
        }
        temp = temp->next;
    }
    
    return 0;
}

int main(){
    int k, id;
    scanf("%d", &k);
    
    Node *head = NULL;

    char* levels[3] = {"Critical", "Serious", "Stable"};
    while (k){
        char* severityLevel = (char *)malloc(sizeof(char)*20);
        scanf("%d %s", &id, severityLevel);
        if(getIndex(severityLevel, levels) == -1 || isIdPresent(head, id)){
            printf("Invalid Input\n");
            continue;
        }

        insertNode(&head, id, severityLevel);
        k--;
    }

    head = mergeSort(head, levels);
    printf("\nSorted List:\n");
    printList(head);

    return 0;
}
