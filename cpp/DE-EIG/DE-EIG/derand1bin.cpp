#include "stdafx.h"
using std::vector;

void derand1bin(vector<double> &xmin, double &fmin, double lb[], double ub[], int maxfunevals, int D)
{
	// Algorithmic parameters
	int				NP	= 5 * D;
	double			F	= 0.7;
	vector<double>	CR;

	for (int i = 0; i < NP; ++i)
	{
		CR.push_back(0.5);
	}

	// Initialize population (4)
	vector<vector<double>> X;
	for (int i = 0; i < NP; ++i)
	{
		vector<double> xi;
		for (int j = 0; j < D; ++j)
		{
			double xij = lb[j] + (ub[j] - lb[j]) * ((double) rand() / RAND_MAX);
			xi.push_back(xij);
		}
		X.push_back(xi);
	}

	vector<vector<double>> V = X;
	vector<vector<double>> U = X;
	
	// Evaluation
	int counteval = 0;
	vector<double> f;
	for (int i = 0; i < NP; ++i)
	{
		f.push_back(ellipsoidalrot(X[i].data()));
	}
	counteval = counteval + NP;

	while (counteval <= maxfunevals - NP)
	{
		// Mutation (5)
		for (int i = 0; i < NP; ++i)
		{
			int r1 = rand() % NP;
			int r2 = rand() % NP;
			int r3 = rand() % NP;
			while (r2 == r3)
			{
				r3 = rand() % NP;
			}
			for (int j = 0; j < D; ++j)
			{
				V[i][j] = X[r1][j] + F * (X[r2][j] - X[r3][j]);
			}
		}
		
		// Crossover (10)
		for (int i = 0; i < NP; ++i)
		{
			bincrossover(U[i], X[i], V[i], CR[i], D);
		}

		// Selection (11)
		for (int i = 0; i < NP; ++i)
		{
			double fui = ellipsoidalrot(U[i].data());
			if (fui < f[i])
			{
				f[i] = fui;
				for (int j = 0; j < D; ++j)
				{
					X[i][j] = U[i][j];
				}
			}
		}
		counteval += NP;
	}

	int fminidx = 0;
	fmin = f[0];
	for (int i = 1; i < NP; ++i) 
	{
		if (f[i] < fmin)
		{
			fmin = f[i];
			fminidx = i;
		}
	}
	xmin = X[fminidx];
}