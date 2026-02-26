#include <stdio.h>
#include <math.h>

int main()
{   
    int a, b, c;
    double x1, x2, A, B;
    scanf("%d%d%d", &a, &b, &c);
    double panBieShi = pow(b, 2) - 4 * a * c;
    if(panBieShi >= 0)
    {
        x1 = (-b + sqrt(panBieShi)) / (2 * a);
        x2 = (-b - sqrt(panBieShi)) / (2 * a);
        if(x1 == x2)
        {
            printf("%.1f", x1);
        }
        else
        {
            printf("%.1f\n%.1f", x1, x2);
        }
    } 
    else if (panBieShi < 0)
    {  
        A = -(double)b / (2 * a);
        if(A == 0.0)
            A = 0.0;
        B = sqrt(-panBieShi) / fabs(2.0 * a);
        printf("%.1f+%.1fi\n%.1f-%.1fi", A, B, A, B);
    }
    return 0;
}