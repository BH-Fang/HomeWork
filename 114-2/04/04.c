#include <stdio.h>

int main() 
{
    int w, h;

    scanf("%d", &w);
    scanf("%d", &h);
    if (w < 20 || w > 100 || h < 100 || h > 200) 
    {
        printf("ERROR");
        return 0;
    }
    double hm = h / 100.0;
    double bmi = w / (hm * hm);
    int whole = (int)bmi;
    int first = ((int)(bmi * 10.0)) % 10;
    int rounded;
    if (first <= 4) 
    {
        rounded = whole;
    } else if (first >= 6) 
    {
        rounded = whole + 1;
    } else 
    {
        if (whole % 2 == 0)
            rounded = whole + 1;
        else
            rounded = whole;
    }
    printf("%d", rounded);
    if (rounded < 18)
        printf("\ntoo low");
    else if (rounded > 24)
        printf("\ntoo high");
    return 0;
}
