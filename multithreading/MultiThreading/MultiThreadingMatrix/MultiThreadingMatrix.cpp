#include "pch.h"
#include <omp.h>
#include <iostream>
#include <ctime>
#include  <cstdlib>
using namespace std;

double t1, t2;
const int n = 5000;
double x[n];
double y[n];
double a[n][n];
double result[n];
double tmp;



int main()
{
	// Without threads
	
	for (int i = 0; i < n; i++) {
		x[i] = (double)i;
	}

	for (int i = 0; i < n; i++) {
		y[i] = (double)i;
	}


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = (double)rand()*i*j;
	
		}
		
	}

	clock_t begin = clock();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tmp += a[i][j] * y[j];
		}

		result[i] = x[i] + tmp;

	}

	clock_t end = clock();
	double elapsed_secs1 = double(end - begin) / CLOCKS_PER_SEC;
	
	// With determined number of threads
	begin = clock();
	omp_set_num_threads(8);

#pragma omp parallel for schedule ( static)// reduction(+:result)
	for (int i = 0; i < n; i++)
	{
#pragma omp parallel for schedule ( static) reduction(+:tmp)
		for (int j = 0; j < n; j++)
		{
			tmp += a[i][j] * y[j];
		}

		result[i] = x[i] + tmp;
	}
	
	
	end = clock();
	double elapsed_secs2 = double(end - begin) / CLOCKS_PER_SEC;
	cout << endl <<  "without multi " << elapsed_secs1 << "s" << endl;
	cout << "with multi " << elapsed_secs2 << "s" << endl;
}


