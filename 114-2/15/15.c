#include <stdio.h>

void match(int *teamWins, int *scores)
{
    int team1Score = 0, team2Score = 0;
    char getTeam1, getTeam2;
    int indexOfTeam1, indexOfTeam2;
    
    scanf(" %c %c", &getTeam1, &getTeam2);
    
    indexOfTeam1 = getTeam1 - 'A';
    indexOfTeam2 = getTeam2 - 'A';
    for(int i = 0; i < 4; i++)
    {
        int score1, score2;
        scanf("%d%d", &score1, &score2);
        team1Score += score1;
        scores[indexOfTeam1] += score1;
        team2Score += score2;
        scores[indexOfTeam2] += score2;
    }
    if(team1Score > team2Score)
        teamWins[indexOfTeam1] += 1;
    else
        teamWins[indexOfTeam2] += 1; 
}

int main()
{
    int M;
    int teamWins[3] = {0}, scores[3] = {0};

    scanf("%d", &M);
    
    for(int i = 0; i < M; i++)
    {
        match(teamWins, scores);
    }
    int indexOfWinner = 0, maxWins = teamWins[0];
    for(int i = 1; i < 3; i++)
    {
        if(teamWins[i] > maxWins)
        {
            indexOfWinner = i;
            maxWins = teamWins[i];
        }
    }

    printf("%c %d", indexOfWinner + 'A', scores[indexOfWinner]);
    return 0;
}