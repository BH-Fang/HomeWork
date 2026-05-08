#include <stdio.h>
#include <math.h>

double f1(double x, double a)
{
    return sqrt(a + pow(x, 2));
}

double f2(double x, double a)
{
    return (a * pow(x, 3) + 7 * x) / sqrt(a + x);
}

double area(double (*f)(double x, double a), double a, double p, double q, int n) 
{
    double h = (q - p) / n;
    double sum = 0.0;
    for (int i = 1; i < n; i++) 
    {
        double xi = p + i * h;
        sum += f(xi, a);
    }
    return (h / 2.0) * (f(p, a) + f(q, a) + 2.0 * sum);
}

int main()
{
    int t, err;
    double a, p, q, n = 2;

    scanf("%d%lf%lf%lf%d", &t, &a, &p, &q, &err);
    double (*func)(double, double) = (t == 1) ? f1 : f2;

    double prev_area = area(func, a, p, q, n);
    double curr_area = 0.0;
    double threshold = pow(10, -err);
    while (1) 
    {
        n *= 2;
        curr_area = area(func, a, p, q, n);
        if (fabs(curr_area - prev_area) < threshold) 
            break;
        prev_area = curr_area;
    }

    printf("answer=%.8lf\n", curr_area);
}