#include "stdafx.h"
using std::vector;

void eigcrossover(
	vector<double> &u, 
	const vector<double> &x, 
	const vector<double> &v, 
	const double CR, 
	const int D, 
	const vector<vector<double>> &Q)
{
	// Eigenvector-based crossover (15)	
	vector<double> ut = u;
	vector<double> xt = x;
	vector<double> vt = v;

	for (int j = 0; j < D; ++j)
	{
		xt[j] = 0;
		vt[j] = 0;
		for (int k = 0; k < D; ++k)
		{
			xt[j] += Q[k][j] * x[k];
			vt[j] += Q[k][j] * v[k];
		}
	}

	int jrand = rand() % D;
	for (int j = 0; j < D; ++j)
	{
		if ((double) rand() / RAND_MAX < CR ||
			j == jrand)
		{
			ut[j] = vt[j];
		} else
		{
			ut[j] = xt[j];
		}
	}

	for (int j = 0; j < D; ++j)
	{
		u[j] = 0;
		for (int k = 0; k < D; ++k)
		{
			u[j] += Q[j][k] * ut[k];
		}
	}
}