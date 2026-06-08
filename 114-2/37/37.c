#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node_t;

Node_t* createNode(int value)
{
    Node_t *newNode = (Node_t*)malloc(sizeof(Node_t));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
} 

void printLinklist(Node_t *dummy, int power)
{
    Node_t *cur = dummy->next;
    int i = power;
    int isFirstTerm = 1;
    int printedAnything = 0; 

    while(cur != NULL)
    {
        int val = cur->value;
        if (val == 0) {
            if (i == 0 && !printedAnything) 
            {
                printf("0");
                printedAnything = 1;
            }
            cur = cur->next;
            i--;
            continue;
        }
        if (val > 0) 
        {
            if (!isFirstTerm) 
            {
                printf("+");
            }
        } else 
        {
            printf("-");
            val = -val;
        }
        isFirstTerm = 0;
        printedAnything = 1;
        if (i == 0) 
        {
            printf("%d", val);
        } else if (i == 1) 
        {
            if (val == 1) printf("x");
            else printf("%dx", val);
        } else 
        {
            if (val == 1) printf("x^%d", i);
            else printf("%dx^%d", val, i);
        }
        
        cur = cur->next;
        i--;
    }
    printf("\n");
}

int main()
{
    Node_t *dummy1 = createNode(0), *dummy2 = createNode(0), *dummy3 = createNode(0);
    Node_t *cur1 = dummy1, *cur2 = dummy2, *cur3 = dummy3;
    int power1 = -1, power2 = -1;
    char input[50], del[] = " ";

    fgets(input, 50, stdin);
    input[(int)strcspn(input, "\n")] = '\0';
    char *token = strtok(input, del);
    while(token != NULL)
    {
        cur1->next = createNode(atoi(token));
        cur1 = cur1->next;
        power1++;
        token = strtok(NULL, del);
    }
    fgets(input, 50, stdin);
    input[(int)strcspn(input, "\n")] = '\0';
    token = strtok(input, del);
    while(token != NULL)
    {
        cur2->next = createNode(atoi(token));
        cur2 = cur2->next;
        power2++;
        token = strtok(NULL, del);
    }

    int p1p2Compare = power1 - power2;
    cur1 = dummy1; cur2 = dummy2;
    if(p1p2Compare > 0)
    {
        for(int i = 0; i < p1p2Compare; i++)
        {
            cur1 = cur1->next;
            cur3->next = createNode(cur1->value);
            cur3 = cur3->next;
        }
    }
    else
    {
        for(int i = 0; i > p1p2Compare; i--)
        {
            cur2 = cur2->next;
            cur3->next = createNode(cur2->value);
            cur3 = cur3->next;
        }
    }
    while(cur1->next != NULL)
    {
        cur1 = cur1->next;
        cur2 = cur2->next;
        cur3->next = createNode(cur1->value + cur2->value);
        cur3 = cur3->next;
    }

    printLinklist(dummy3, power1>power2?power1:power2);

    return 0;
}