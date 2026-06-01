#include <stdio.h>

typedef struct node_p
{
    int cost;
    struct node_p* next[99];
    int k;
    int is;         
    int max_time;   
} node_t;

typedef struct 
{
    node_t nodes[100];
    int m;
} Program;

int dfs(node_t* currentNode)
{   
    if (currentNode->max_time > 0) {
        return currentNode->max_time;
    }

    int max_child_time = 0;
    
    for(int i = 0; i < currentNode->k; i++)
    {
        int child_time = dfs(currentNode->next[i]);
        if (child_time > max_child_time) {
            max_child_time = child_time;
        }
    }

    currentNode->max_time = currentNode->cost + max_child_time;
    
    return currentNode->max_time;
}

int main()
{
    Program programs[3];
    int N, result[3] = {0}; 

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {   
        scanf("%d", &programs[i].m);
        for(int j = 0; j < programs[i].m; j++) 
        {
            programs[i].nodes[j].is = 0;
            programs[i].nodes[j].max_time = 0;
        }
        
        for(int j = 0; j < programs[i].m; j++)
        {   
            scanf("%d %d", &programs[i].nodes[j].cost, &programs[i].nodes[j].k);
            for(int k = 0; k < programs[i].nodes[j].k; k++)
            {   
                int t;
                scanf("%d", &t);
                programs[i].nodes[j].next[k] = &programs[i].nodes[t - 1];
                programs[i].nodes[t - 1].is += 1;
            }
        }
    }

    for(int i = 0; i < N; i++)
    {
        int max_project_time = 0;
        
        for(int j = 0; j < programs[i].m; j++)
        {
            if(programs[i].nodes[j].is == 0)
            {
                int current_path_time = dfs(&programs[i].nodes[j]);
                if (current_path_time > max_project_time) {
                    max_project_time = current_path_time;
                }
            }
        }
        result[i] = max_project_time;
    }

    for(int i = 0; i < N; i++)
    {
        printf("%d\n", result[i]);
    }

    return 0;
}