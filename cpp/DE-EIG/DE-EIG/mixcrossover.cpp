#include "stdafx.h"
using std::vector;

void mixcrossover(
	vector<double> &u, 
	const vector<double> &x, 
	const vector<double> &v, 
	const double CR, 
	const int D, 
	const vector<vector<double>> &Q,
	const double P)
{
	// Mix Crossover (16)
	if ((double) rand() / RAND_MAX < P)
	{
		eigcrossover(u, x, v, CR, D, Q);
	} else
	{			
		bincrossover(u, x, v, CR, D);
	}
}