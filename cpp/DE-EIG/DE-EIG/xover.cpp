#include "stdafx.h"
using std::vector;

void xover(
	vector<vector<double>> &U, 
	const vector<vector<double>> &X, 
	const vector<vector<double>> &V,
	const vector<double> &CR,
	const int D,
	const double P,
	const int NP)
{		
	// Covariance matrix (12)
	vector<vector<double>>	C;	
	vector<double>			m = X[0];
	
	for (int i = 0; i < D; ++i)
	{
		vector<double> ci;
		for (int j = 0; j < D; ++j)
		{
			ci.push_back(0);
		}
		C.push_back(ci);
	}

	for (int i = 1; i < NP; ++i)
	{
		for (int j = 0; j < D; ++j)
		{
			m[j] += X[i][j];
		}
	}
	for (int i = 0; i < D; ++i)
	{
		m[i] /= NP;
	}

	for (int i = 0; i < D; ++i)
	{
		for (int j = 0; j < D; ++j)
		{
			C[i][j] = 0;
			for (int k = 0; k < NP; ++k)
			{
				C[i][j] += (X[k][i] - m[i]) * (X[k][j] - m[j]);
			}
			C[i][j] /= (NP - 1);
		}
	}
	
	// Eigendecomposition (14)
	double*					L	= new double[D];	
	vector<vector<double>>	Q	= C;
	double*					tmp = new double[D + 1];

	Eigen(D, C, L, Q, tmp);

	// Crossover (16)
	for (int i = 0; i < NP; ++i)
	{
		mixcrossover(U[i], X[i], V[i], CR[i], D, Q, P);
	}
}