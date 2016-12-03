/******************************************************************************
* FILE: omp_workshare1.c
* DESCRIPTION:
*   OpenMP Example - Loop Work-sharing - C/C++ Version
*   In this example, the iterations of a loop are scheduled dynamically
*   across the team of threads.  A thread will perform CHUNK iterations
*   at a time before being scheduled for the next CHUNK of work.
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define CHUNKSIZE 10
#define N 100

int main (int argc, char *argv[]) {

    int nthreads, tid, i, chunk;
    float a[N], b[N], c[N];

    /* Some initializations */
    for (i=0; i < N; i++) {
        a[i] = b[i] = i * 1.0;
    }
    chunk = CHUNKSIZE;

    #pragma omp parallel shared(a,b,c,nthreads,chunk) private(i,tid)
    {
    tid = omp_get_thread_num();
    if (tid == 0) {
        nthreads = omp_get_num_threads();
        printf("Number of threads = %d\n", nthreads);
    }
    printf("Thread %d starting...\n", tid);

    /* If I put static schedule the thread 0 gets the first chunk (i=0...9), the thread 1 gets the second chunk (i=10...19),
    the thread 2 gets the third chunk (i=20...29), the thread 3 gets the fourth chunk (i=30...39) and then the thread 0
    gets the five-th chunk (i=40...49) and so on. In both of cases there are 2 thread that execute 1 more chunk in order to
    complete the N iterations */
    #pragma omp for schedule(dynamic,chunk)
    for (i=0; i<N; i++) {
        c[i] = a[i] + b[i];
        printf("Thread %d: c[%d]= %f\n", tid, i, c[i]);
    }
    } /* end of parallel section */
}
