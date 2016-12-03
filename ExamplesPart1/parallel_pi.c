#include <stdio.h>
#include <omp.h>

//Global variables
static long num_steps;
double step, pi;

//Prototype for the function
void calculate_pi(int);

void main() {

	printf("Insert the numbers of steps: ");
	scanf("%d", &num_steps);

	double t_in = omp_get_wtime();
   	step = 1.0/(double) num_steps;

	int num_threads = 2;

   	calculate_pi(num_threads);

	double t_fin = omp_get_wtime();
   	printf("Pi = %f\n", pi);
	printf("Wall clock time = %.9f sec\n", t_fin-t_in);
	printf("Number of threads = %d\n", num_threads);
}

void calculate_pi(int num_threads) {

	double x, sum = 0.0;
	int i;

	omp_set_num_threads(num_threads);

	#pragma omp parallel for private(x) reduction(+:sum)
   	for (i=0; i<num_steps; i++){
      		x = (i+0.5)*step;
      		sum = sum + 4.0/(1.0 + x*x);
   	}

	pi = step * sum;
}

