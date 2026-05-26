#include <stdio.h>

typedef struct 
{
    int machine, cost;
} Process;

typedef struct 
{
    Process processes[10];
    int n, now_processing, last_process_time;
} Work;

int max(int a, int b)
{
    return a > b ? a : b;
}

int calc_time(int machine[], Work work)
{
    return max(work.last_process_time, machine[work.processes[work.now_processing].machine]) + work.processes[work.now_processing].cost;
}

int main()
{
    int M, N, total_time = 0, done_works = 0;
    Work works[10];
    int machine_time[10] = {0};

    scanf("%d%d", &N, &M);
    for(int i = 0; i < M; i++)
    {
        scanf("%d", &works[i].n);
        works[i].now_processing = 0; 
        works[i].last_process_time = 0;
        for(int j = 0; j < works[i].n; j++)
        {
            scanf("%d%d", &works[i].processes[j].machine, &works[i].processes[j].cost);
        }
    }


    while(done_works < M)
    {
        int min_index = -1, min_time = __INT32_MAX__;
        for(int i = 0; i < M; i++)
        {   
            if(works[i].now_processing < works[i].n) 
            {
                int t = calc_time(machine_time, works[i]);
                if(t < min_time)
                {
                    min_index = i;
                    min_time = t;
                }
            }
        }
        int m_id = works[min_index].processes[works[min_index].now_processing].machine;
        machine_time[m_id] = min_time;
        works[min_index].last_process_time = min_time;
        works[min_index].now_processing += 1;
        if(works[min_index].now_processing == works[min_index].n)
        {
            done_works++;
        }
    }
    for(int i = 0; i < M; i++)
    {
        total_time += works[i].last_process_time;
    }
    
    printf("%d\n", total_time);
    return 0;
}