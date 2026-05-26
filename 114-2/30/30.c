#include <stdio.h>
#include <string.h>

typedef enum { OUT, BASE_HIT } play_type_t;

typedef union {
    int base_hit;   /* 1~4: number of bases */
    char out_kind;  /* 'F', 'S', 'G' */
} play_result_t;

typedef struct {
    play_type_t type;
    play_result_t result;
} play_t;

typedef struct {
    int no;
    play_t data[5];
} basePlayer_t;

#define PLAYERS 9

static void parsePlay(const char *s, play_t *p)
{
    if (strcmp(s, "1B") == 0) {
        p->type = BASE_HIT;
        p->result.base_hit = 1;
    } else if (strcmp(s, "2B") == 0) {
        p->type = BASE_HIT;
        p->result.base_hit = 2;
    } else if (strcmp(s, "3B") == 0) {
        p->type = BASE_HIT;
        p->result.base_hit = 3;
    } else if (strcmp(s, "HR") == 0) {
        p->type = BASE_HIT;
        p->result.base_hit = 4;
    } else if (strcmp(s, "FO") == 0) {
        p->type = OUT;
        p->result.out_kind = 'F';
    } else if (strcmp(s, "GO") == 0) {
        p->type = OUT;
        p->result.out_kind = 'G';
    } else if (strcmp(s, "SO") == 0) {
        p->type = OUT;
        p->result.out_kind = 'S';
    }
}

static void advanceBases(int bases[4], int k, int *score)
{
    int nb[4] = {0, 0, 0, 0};

    for (int pos = 3; pos >= 1; pos--) {
        if (!bases[pos])
            continue;
        int np = pos + k;
        if (np >= 4)
            (*score)++;
        else
            nb[np] = 1;
    }

    int np = k;
    if (np >= 4)
        (*score)++;
    else
        nb[np] = 1;

    bases[1] = nb[1];
    bases[2] = nb[2];
    bases[3] = nb[3];
}

int main(void)
{
    basePlayer_t team[PLAYERS];
    int atBatIdx[PLAYERS] = {0};

    for (int i = 0; i < PLAYERS; i++) {
        scanf("%d", &team[i].no);
        for (int j = 0; j < team[i].no; j++) {
            char s[8];
            scanf("%s", s);
            parsePlay(s, &team[i].data[j]);
        }
    }

    int targetOuts;
    scanf("%d", &targetOuts);

    int outs = 0;
    int score = 0;
    int bases[4] = {0, 0, 0, 0};
    int batter = 0;

    while (outs < targetOuts) {
        play_t *play = &team[batter].data[atBatIdx[batter]++];
        if (play->type == OUT) {
            outs++;
            if (outs % 3 == 0) {
                bases[1] = 0;
                bases[2] = 0;
                bases[3] = 0;
            }
        } else {
            advanceBases(bases, play->result.base_hit, &score);
        }
        batter = (batter + 1) % PLAYERS;
    }

    printf("%d\n", score);
    return 0;
}
