#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SPACE " "
#define DQUOTES "\""

typedef struct Node
{
    char name[50];
    int age, birthday[3];
    struct Node *next;
} Node_t;

Node_t* createNode(char *name, int age, int birthday_year, int birthday_month, int birthday_day)
{
    Node_t *newNode = (Node_t*)malloc(sizeof(Node_t));
    strcpy(newNode->name, name);
    newNode->age = age;
    newNode->birthday[0] = birthday_year;
    newNode->birthday[1] = birthday_month;
    newNode->birthday[2] = birthday_day;
    newNode->next = NULL;
    return newNode;
}

void push(Node_t* dummy, Node_t* node)
{
    Node_t *cur = dummy;
    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = node;
}

Node_t* pop(Node_t* dummy)
{
    Node_t *cur = dummy, *ret;
    while(cur->next->next != NULL)
    {
        cur = cur->next;
    }
    ret = cur->next;
    cur->next = NULL;
    return ret;
}

int main()
{
    Node_t *dummy = createNode("", 0, 0, 0, 0);
    int cmd = 0;
    do
    {
        if(cmd == 1)
        {
            char str[100], name[50];
            int age, year, month, day;

            getchar();
            fgets(str, 100, stdin);
            str[(int)strcspn(str, "\n")] = '\0';
            char *token = strtok(str, DQUOTES);
            strcpy(name, token);
            token = strtok(NULL, SPACE);
            age = atoi(token);
            token = strtok(NULL, SPACE);
            year = atoi(token);
            token = strtok(NULL, SPACE);
            month = atoi(token);
            token = strtok(NULL, SPACE);
            day = atoi(token);

            push(dummy, createNode(str + 1, age, year, month, day));
        } 
        else if (cmd == 2)
        {
            int type;
            scanf("%d", &type);
            if(dummy->next == NULL)
            {
                printf("The Stack is empty\n");
            } else if(type == 1)
            {
                printf("%s\n", pop(dummy)->name);
            } else if (type == 2)
            {
                printf("%d\n", pop(dummy)->age);
            } else if (type == 3)
            {
                Node_t *t = pop(dummy);
                printf("%d_%d_%d\n", t->birthday[0], t->birthday[1], t->birthday[2]);
            }
        }
        scanf("%d", &cmd);
    } while (cmd != 3);
    
    return 0;
}