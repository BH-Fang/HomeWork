#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dnode_s 
{
int data;
struct dnode_s * front;
struct dnode_s * back;
} node_t;
typedef node_t * nodep_t; 

nodep_t creatNode(int data)
{
    nodep_t newNode = (nodep_t)malloc(sizeof(node_t));
    newNode->back = NULL;
    newNode->front = NULL;
    newNode->data = data;
    return newNode;
}

void addFront(nodep_t dummy, int data)
{
    nodep_t newNode = creatNode(data);
    newNode->back = dummy->back;
    newNode->front = dummy;
    if(dummy->back != NULL)
        dummy->back->front = newNode;
    dummy->back = newNode;
}

void addBack(nodep_t dummy, int data)
{
    nodep_t newNode = creatNode(data), preNode = dummy;
    while(preNode->back != NULL)
    {
        preNode = preNode->back;
    }
    preNode->back = newNode;
    newNode->front = preNode;
}

int removeFront(nodep_t dummy)
{
    if(dummy->back == NULL)
        return 0;
    nodep_t head = dummy->back;
    dummy->back = head->back;
    if(head->back != NULL)
        head->back->front = dummy;
    free(head);
    return 1;
}

int removeBack(nodep_t dummy)
{
    if(dummy->back == NULL)
        return 0;
    nodep_t tail = dummy->back;
    while(tail->back != NULL)
    {
        tail = tail->back;
    }
    tail->front->back = NULL;
    free(tail);
    return 1;
}

int empty(nodep_t dummy)
{
    if(dummy->back == NULL)
        return 0;
    nodep_t current = dummy;
    while(current->back->back != NULL)
    {
        current = current->back;
    }
    while(current->front != NULL)
    {
        free(current->back);
        current = current->front;
    }
    free(current->back);
    dummy->back = NULL;
    return 1;    
}

int insert(nodep_t dummy, int n, int data)
{
    int i = 0;
    nodep_t current = dummy;
    while(i < n)
    {
        if(current->back != NULL)
        {
            current = current->back;
            i++;
        }
        else
            return 0;
    }
    nodep_t newNode = creatNode(data);
    if(current->back != NULL)
        current->back->front = newNode;
    newNode->back = current->back;
    newNode->front = current;
    current->back = newNode;
    return 1;
}

int removeNode(nodep_t dummy, int n)
{
    int i = 0;
    nodep_t current = dummy;
    while(i < n)
    {
        if(current->back != NULL)
        {
            current = current->back;
            i++;
        }
        else
            return 0;
    }
    if(current->back != NULL)
        current->back->front = current->front;
    current->front->back = current->back;
    free(current);
    return 1;
}

int print(nodep_t dummy)
{
    if(dummy->back == NULL)
        return 0;
    nodep_t current = dummy;
    while(current->back != NULL)
    {
        current = current->back;
        printf("%d\n", current->data);
    }
    return 1;
}

int main()
{
    int N;
    char cmd[50];
    nodep_t dummy = creatNode(0);
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%s", cmd);
        if(strcmp(cmd, "addFront") == 0)
        {
            int data;
            scanf("%d", &data);
            addFront(dummy, data);
        }
        else if(strcmp(cmd, "addBack") == 0)
        {
            int data;
            scanf("%d", &data);
            addBack(dummy, data);
        }
        else if(strcmp(cmd, "removeFront") == 0)
        {
            if(!removeFront(dummy))
                printf("Double link list is empty\n");
        }
        else if(strcmp(cmd, "removeBack") == 0)
        {
            if(!removeBack(dummy))
                printf("Double link list is empty\n");
        }
        else if(strcmp(cmd, "empty") == 0)
        {
            if(!empty(dummy))
                printf("Double link list is empty\n");
        }
        else if(strcmp(cmd, "insert") == 0)
        {
            int n, data;
            scanf("%d %d", &n, &data);
            if(!insert(dummy, n, data))
                printf("Invalid command\n");
        }
        else if(strcmp(cmd, "remove") == 0)
        {
            int n;
            scanf("%d", &n);
            if(!removeNode(dummy, n))
                printf("Invalid command\n");
        }
        else if(strcmp(cmd, "print") == 0)
        {
            if(!print(dummy))
                printf("Double link list is empty\n");
        }
    }
    return 0;
}