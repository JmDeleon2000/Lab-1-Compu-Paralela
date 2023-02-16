#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

double pi(int);

int main(int argc, char* argv[])
{
    int N = 100000;
    if (argc > 1)
        N = strtol(argv[1], NULL, 10);

    double start_t = omp_get_wtime();
    double piAprox = pi(N);
    double end_t = omp_get_wtime();


    printf("Pi:\t%.10f\n", piAprox);
    printf("Iterations:\t%d\n", N);
    printf("Time:\t%.10f\n", end_t - start_t);

    return 0;
}

double pi(int n)
{
    double factor = 1.0;
    double sum = 0.0;

    for(int k = 0; k < n; k++)
    {
        sum += factor/(2*k+1);
        factor = -factor;
    }

    return 4.0*sum;
}