#include <stdio.h>

const int type_name[] = {183, 383, 983};
const int free_voice_in[] = {500, 600, 700};
const int free_voice_out[] = {400, 500, 600};
const int free_homephone[] = {300, 400, 500};
const int free_message_in[] = {10, 20, 30};
const int free_message_out[] = {15, 25, 35};
const float voice_in_cost[] = {0.08, 0.07, 0.06};
const float voice_out_cost[] = {0.1393, 0.1304, 0.1087};
const float homephone_cost[] = {0.1349, 0.1217, 0.1018};
const float message_in_cost[] = {1.1287, 1.1127, 0.9572};
const float message_out_cost[] = {1.4803, 1.2458, 1.1243};

int cost(int type, int voice_in, int voice_out, int homephone, int message_in, int message_out)
{
    float result = 0;
    float vic = (voice_in > free_voice_in[type]? (float)(voice_in - free_voice_in[type]) * voice_in_cost[type]: 0);
    float voc = (voice_out > free_voice_out[type]? (float)(voice_out - free_voice_out[type]) * voice_out_cost[type]: 0);
    float hpc = (homephone > free_homephone[type]? (float)(homephone - free_homephone[type]) * homephone_cost[type]: 0);
    float mic = (message_in > free_message_in[type]? (float)(message_in - free_message_in[type]) * message_in_cost[type]: 0);
    float moc = (message_out > free_message_out[type]? (float)(message_out - free_message_out[type]) * message_out_cost[type]: 0);
    result = vic + voc + hpc +mic + moc;
    if(result < (float)type_name[type])
    {
        result = (float)type_name[type];
    }
    return (int)result;
}

int main()
{   
    int voice_in, voice_out, homephone, message_in, message_out;
    scanf("%d %d %d %d %d", &voice_in, &voice_out, &homephone, &message_in, &message_out);
    int best_cost = __INT32_MAX__, best_type = 0;
    for(int i = 0; i < 3; i++)
    {
        int c = cost(i, voice_in, voice_out, homephone, message_in, message_out);
        if(c < best_cost)
        {
            best_cost = c;
            best_type = i;
        }
    }
    printf("%d\n%d", best_cost, type_name[best_type]);
    return 0;
}