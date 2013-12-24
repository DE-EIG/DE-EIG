#include "stdafx.h"
using std::vector;

void bincrossover(
	vector<double> &u, 
	const vector<double> &x, 
	const vector<double> &v, 
	const double CR, 
	const int D)
{
	// Binomial Crossover (10)
	int jrand = rand() % D;
	for (int j = 0; j < D; ++j)
	{
		if ((double) rand() / RAND_MAX < CR ||
			j == jrand)
		{
			u[j] = v[j];
		} else
		{
			u[j] = x[j];
		}
	}
}