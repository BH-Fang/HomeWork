#include <stdio.h>

void cardInput(float *player_score)
{
    for(int i = 0; i < 3; i++)
    {
        char input[3];
        scanf("%s", input);
        if(input[0] == '1' && input[1] == '0') *player_score += 10;
        else if(input[0] == 'A') *player_score += 1;
        else if(input[0] == 'J') *player_score += 0.5;
        else if(input[0] == 'Q') *player_score += 0.5;
        else if(input[0] == 'K') *player_score += 0.5;
        else if(input[0] >= 49 && input[0] <= 57) *player_score += input[0] - 48;
    }
    if(*player_score > 10.5) *player_score = 0;
}

int main()
{
    float scoreX = 0, scoreY = 0;
    cardInput(&scoreX);
    cardInput(&scoreY);
    printf("%g\n%g\n%s", scoreX, scoreY, scoreX > scoreY ? "X Win" : (scoreX < scoreY ? "Y Win" : "Tie"));   
    return 0;
}