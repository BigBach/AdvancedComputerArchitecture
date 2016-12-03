#include <stdio.h>
#include <omp.h>
#define DEPTHMAX 4

int split(int *, int, int);
void quicksort(int *, int, int, int);
void quicksortSerial (int *, int, int, int);

int main(int argc, char *argv[]) {

    int arr[10] = {11,2,9,13,57,25,17,1,90,3};
	int i;

	double t_in = omp_get_wtime();
	quicksort(arr,0,9,0);
    double t_fin = omp_get_wtime();
	printf("Array after sorting:\n");

	for (i = 0; i <= 9; i++) {
		printf ("%d\t", arr[i]);
	}
    printf("\nWall clock time = %.7f sec\n", t_fin-t_in);
}

void quicksort (int a[], int lower, int upper, int depth) {

    if (depth > DEPTHMAX) {
        quicksortSerial(a, lower, upper, depth);
        return;
    }

	int i, section;

	if (upper > lower) {
		i = split (a, lower, upper);
		#pragma omp parallel
		{
		#pragma omp sections
		{
            #pragma omp section
            quicksort(a, lower, i - 1 , depth + 1);
            #pragma omp section
            quicksort(a, i + 1, upper, depth + 1);
		}
        }
    }
}

void quicksortSerial (int a[], int lower, int upper, int depth) {

	int i, section;
	if (upper > lower) {
        i = split (a, lower, upper);
		quicksort(a, lower, i - 1, depth);
		quicksort(a, i + 1, upper, depth);
    }
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
