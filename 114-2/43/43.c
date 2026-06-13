#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s 
{
    char data;
    struct node_s *right, * left;
} tree_t;
typedef tree_t* btree; 

btree creatNode(char data)
{
    btree newNode = (btree)malloc(sizeof(tree_t));
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode; 
}

int findIndex(char *I, int start, int end, char target)
{
    for(int i = start; i < end; i++)
    {
        if(I[i] == target)
            return i;
    }
    return -1;
}

btree buildPI(char *P, char *I, int Istart, int Iend, int *Pindex)
{
    if(Istart >= Iend) 
        return NULL;
    char rootData = P[*Pindex];
    btree root = creatNode(rootData);
    int Iindex = findIndex(I, Istart, Iend, rootData);
    (*Pindex)++;
    root->left = buildPI(P, I, Istart, Iindex, Pindex);
    root->right = buildPI(P, I, Iindex + 1, Iend, Pindex);
    return root;
}

btree buildOI(char *O, char *I, int Istart, int Iend, int *Oindex)
{
    if(Istart >= Iend) 
        return NULL;
    char rootData = O[*Oindex];
    btree root = creatNode(rootData);
    int Iindex = findIndex(I, Istart, Iend, rootData);
    (*Oindex)--;
    root->right = buildOI(O, I, Iindex + 1, Iend, Oindex);
    root->left = buildOI(O, I, Istart, Iindex, Oindex);
    return root;
}

void printTree(btree root)
{
    btree q[500];
    int front = 0, rear = 0;
    q[rear++] = root;
    while(front != rear)
    {
        btree current = q[front++];
        if(current->left != NULL)
            q[rear++] = current->left;
        if(current->right != NULL)
            q[rear++] = current->right;
        printf("%c", current->data);
    }
    printf("\n");
}

int main()
{
    char PIO;
    char P[25] = "", I[25] = "", O[25] = "";
    btree result;
    int Pindex = 0, Oindex;

    for(int i = 0; i < 2; i++)
    {
        scanf(" %c", &PIO);
        if(PIO == 'P')
            scanf("%s", P);
        else if(PIO == 'I')
            scanf("%s", I);
        else if(PIO == 'O')
            scanf("%s", O);
    }
    
    if(strlen(P))
    {
        result = buildPI(P, I, 0, strlen(I), &Pindex);
    }
    else
    {
        Oindex = strlen(O) - 1;
        result = buildOI(O, I, 0, strlen(I), &Oindex);
    }

    printTree(result);

    return 0;
}