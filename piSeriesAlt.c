#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

double pi(int, int);

int main(int argc, char* argv[])
{
    int N = 10e6;
    int thread_count = 2;
    if (argc > 2)
        N = strtol(argv[1], NULL, 10);
        thread_count = strtol(argv[2], NULL, 10);

    double start_t = omp_get_wtime();
    double piAprox = pi(N, thread_count);
    double end_t = omp_get_wtime();


    printf("Pi:\t%.10f\n", piAprox);
    printf("Iterations:\t%d\n", N);
    printf("Time:\t%.10f\n", end_t - start_t);

    return 0;
}

double pi(int n, int thread_count)
{
    double evenSum = 0.0;
    double oddSum = 0.0;

    #pragma omp parallel for num_threads(thread_count) \
    reduction(+:evenSum)
    for(int i=0; i<n; i+=2)
    {
      evenSum += 1.0/(2*i+1);
    }

    #pragma omp parallel for num_threads(thread_count) \
    reduction(+:oddSum)
    for(int j = 1; j < n; j+=2)
    {
      oddSum += 1.0/(2*j+1);
    }

    return 4.0*(evenSum - oddSum);
}