// MultiThreadingTests.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <omp.h>
#include <iostream>
#include <ctime>
using namespace std;

int n = 10000000;
double deltaX = 1 / (double)n;
double t1, t2;
double integral = 0.0f;

double fcalc(int i)
{
	return (double)4.0/ (1.0 + powf((i*deltaX), 2));
}



int main()
{


	clock_t begin = clock();
	// Without threads
	
	for (int j = 0; j < n ; j++)
	{
		integral = integral + (fcalc(j) + fcalc(j + 1))*deltaX / 2;
	}
	
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "without multi " << elapsed_secs << "s" << endl;
	cout << integral << endl;
	

	// With determined number of threads
	integral = 0;
	begin = clock();
	omp_set_num_threads(4);

	#pragma omp parallel for reduction(+:integral)
		for (int i = 0; i < n; i++)
		{
					integral = integral + (fcalc(i) + fcalc(i + 1))*deltaX / 2;
				
		}
	
	
	
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout <<"with multi "<< elapsed_secs << "s" << endl;
	cout << integral << endl;
}


