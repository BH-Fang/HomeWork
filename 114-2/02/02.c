#include <stdio.h>

int run(int bases[], int power)
{   
    int score = 0;
    for(int i = 0; i < power; i++)
    {
        if(bases[2])
        {
            score ++;
            bases[2] = 0;
        }
        if(bases[1])
        {
            bases[2] = 1;
            bases[1] = 0;
        }
        if(bases[0])
        {
            bases[1] = 1;
            bases[0] = 0;
        }
        if(!i) bases[0] = 1;
    }
    return score;
}

int main()
{
    int score = 0;
    int bases[3] = {0, 0, 0};
    
    for(int i = 0; i < 3; i++)
    {
        int input = 0;
        scanf("%d", &input);
        score += run(bases, input);
    }

    printf("%d\n%d %d %d", score, bases[0], bases[1], bases[2]);
    return 0;
}