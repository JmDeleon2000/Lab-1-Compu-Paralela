#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

double pi(int, int);

int main(int argc, char* argv[])
{
    int N = 10000000;
    int thread_count = 2;
    if (argc > 2)
        N = strtol(argv[1], NULL, 10);
        thread_count = strtol(argv[2], NULL, 10);

    double start_t = omp_get_wtime();
    double piAprox = pi(N, thread_count);
    double end_t = omp_get_wtime();


    printf("Pi:\t%.20f\n", piAprox);
    printf("Iterations:\t%d\n", N);
    printf("Time:\t%.10f\n", end_t - start_t);

    return 0;
}

double pi(int n, int thread_count)
{
    double factor = 1.0;
    double sum = 0.0;

    #pragma omp parallel for schedule(runtime) \
    num_threads(thread_count) \
    reduction(+:sum) private(factor)
    for(int k = 0; k < n; k++)
    {
        factor = (k % 2 == 0) ? 1.0 : -1.0;
        sum += factor/(2*k+1);
    }

    return 4.0*sum;
}