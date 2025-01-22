#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList{
    Node *head;
    Node *tail;
} LinkedList;

Node* createNode(int data){
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void insertNode(LinkedList *list,  int data){
    Node *newNode = createNode(data);
    
    if(list->head == NULL){
        list->head = newNode;
    }else{
        list->tail->next = newNode;
    }
    
    list->tail = newNode;
}

int main()
{
    int operation, windowSize;
    scanf("%d", &operation);
    scanf("%d", &windowSize);
    while(getchar() != '\n');

    int ans[1000];
    LinkedList list;
    list.head = NULL;
    list.tail = NULL;
    
    char character;
    int number;
    int length = 0;
    int count = 0;
    for(int i=0; i<operation; i++){
        scanf("%c", &character);
      
        if(character == 'A'){
            scanf("%d", &number);
            insertNode(&list, number);
            length++;
        }
        
        while(getchar() != '\n');
        
        if(character == 'S'){
            
           Node *temp = list.head;
           for(int i=0; i< length-windowSize; i++){
               temp = temp->next;
           }
           
           int sum = 0;
           while(temp != NULL){
               sum += temp->data;
               temp = temp->next;
           }
            
            ans[count] = sum;
            count++;
        }
    }
    
    for(int i=0; i<count; i++){
        printf("%d\n", ans[i]);
    }
    return 0;
}
