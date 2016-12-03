#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define DEPTH_MAX 4
#define DEPTH_MIN 1

int split (int *, int, int);
void quicksort (int *, int, int, int);

int main(int argc, char *argv[]) {

    int arr[10] = {11,2,9,13,57,25,17,1,90,3};
	int i, j;

	double t_in = omp_get_wtime();

	#pragma omp parallel
	{
        #pragma omp single
        quicksort(arr, 0, 9 , DEPTH_MIN);
	}

	double t_fin = omp_get_wtime();

	printf ("Array after sorting:\n");

	for (i = 0; i < 10; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
	printf("Wall clock time = %.7f sec\n", t_fin-t_in);
}

void quicksort (int a[], int lower, int upper, int depth) {

	int i;
	if (upper > lower) {
		i = split(a, lower, upper);
		#pragma omp task if (depth > DEPTH_MAX)
		quicksort(a, lower, i - 1, depth +1);
        #pragma omp task if (depth > DEPTH_MAX)
		quicksort(a, i + 1, upper, depth+1);
	}
	#pragma omp taskwait
}

int split (int a[], int lower, int upper) {

	int i, p, q, t;

	p = lower + 1;
	q = upper;
	i = a[lower];

	while (q >= p) {
		while (a[p] < i) {
			p++;
		}
		while (a[q] > i) {
			q--;
		}
		if (q > p) {
			t = a[p];
			a[p] = a[q];
			a[q] = t;
		}
	}

	t = a[lower];
	a[lower] = a[q];
	a[q] = t;

	return q;
}
