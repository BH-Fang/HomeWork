#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SPACE " "

typedef struct Node {
    char word[50];
    struct Node *next;
} Node; 

typedef Node* Node_p;

Node_p creatNode(char *word)
{
    Node_p n = (Node_p)malloc(sizeof(Node));
    strcpy(n->word, word);
    n->next = NULL;
    return n;
}

void pri(Node_p dummy)
{
    Node_p curr = dummy;
    while(curr->next != NULL)
    {
        curr = curr->next;
        printf("%s ", curr->word);
    }
    printf("\n");
}

Node_p insert(Node_p a, char *P, char *Q)
{
    Node_p i = a, dummy = creatNode("");
    Node_p j = dummy;
    while(i->next != NULL)
    {
        i = i->next;
        if(strcmp(i->word, P) == 0)
        {
            j->next = creatNode(Q);
            j = j->next;
        }
        j->next = creatNode(i->word);
        j = j->next;
    }
    return dummy;
}

Node_p replace(const Node_p a, const char *P, const char *Q)
{
    Node_p i = a, dummy = creatNode("");
    Node_p j = dummy;
    while(i->next != NULL)
    {
        i = i->next;
        if(strcmp(i->word, P) == 0)
        {
            j->next = creatNode(Q);
        }
        else
        {
            j->next = creatNode(i->word);
        }
        j = j->next;
    }
    return dummy;
}

Node_p delete(const Node_p a, const char *P, const char *Q)
{
    Node_p i = a, dummy = creatNode("");
    Node_p j = dummy;
    while(i->next != NULL)
    {
        i = i->next;
        if(strcmp(i->word, P))
        {
            j->next = creatNode(i->word);
            j = j->next;
        }
    }
    return dummy;
}

int main()
{
    Node_p dummy = creatNode("");
    char P[50], Q[50], Input[500];

    fgets(Input, 500, stdin);
    Input[strcspn(Input, "\n")] = '\0';
    char *token = strtok(Input, SPACE);
    Node_p curr = dummy;
    while(token != NULL)
    {
        curr->next = creatNode(token);
        curr = curr->next;
        token = strtok(NULL, SPACE);
    }
    scanf("%s%s", P, Q);

    pri(insert(dummy, P, Q));
    pri(replace(dummy, P, Q));
    pri(delete(dummy, P, Q));
    
    return 0;
}