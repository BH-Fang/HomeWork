#include <stdio.h>
#include <string.h>
#define GATEVALUE(Gate) int(*GateValue)(struct _Gate *)  

typedef struct _Gate {
int input1;
int input2;
GATEVALUE(Gate);
}Gate;

int GateORValue(Gate *gate) 
{
    return (gate->input1 | gate->input2) & 7;
}

int GateANDValue(Gate *gate) 
{
    return (gate->input1 & gate->input2) & 7;
}

int GateNOTValue(Gate *gate) 
{
    return (~gate->input1) & 7; 
}

int GateNANDValue(Gate *gate) 
{
    return (~(gate->input1 & gate->input2)) & 7; 
}

int GateNORValue(Gate *gate) 
{
    return (~(gate->input1 | gate->input2)) & 7; 
}

int GateBUFFERValue(Gate *gate) 
{
    return gate->input1 & 7;
}

void CreateGate(Gate *obj, char* type, int in1, int in2)
{
    obj->input1 = in1;
    obj->input2 = in2;
    if (strcmp(type, "O") == 0) obj->GateValue = GateORValue;
    else if (strcmp(type, "A") == 0) obj->GateValue = GateANDValue;
    else if (strcmp(type, "N") == 0) obj->GateValue = GateNOTValue;
    else if (strcmp(type, "B") == 0) obj->GateValue = GateBUFFERValue;
    else if (strcmp(type, "NA") == 0) obj->GateValue = GateNANDValue;
    else if (strcmp(type, "NO") == 0) obj->GateValue = GateNORValue;
}

int main()
{
    int X1, X2, X3, result;
    Gate gates[5];
    scanf("%d%d%d", &X1, &X2, &X3);
    for(int i = 0; i < 5; i++)
    {
        char type[5];
        scanf("%s", type);
        CreateGate(&gates[i], type, 0, 0);
    }

    gates[0].input1 = X1;
    gates[1].input1 = X2;
    gates[2].input1 = X3;
    gates[3].input1 = gates[0].GateValue(&gates[0]);
    gates[3].input2 = gates[1].GateValue(&gates[1]);
    gates[4].input1 = gates[3].GateValue(&gates[3]);
    gates[4].input2 = gates[2].GateValue(&gates[2]);
    result = gates[4].GateValue(&gates[4]);

    printf("%d%d%d\n", (result >> 2) & 1, (result >> 1) & 1, result & 1);
    return 0;
}