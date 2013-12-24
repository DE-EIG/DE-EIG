#include "stdafx.h"
using std::cout;
using std::endl;

int _tmain(int argc, _TCHAR* argv[])
{
	const int		D			= 30;
	const int		T			= 50;
	double			solutionerror[T];
	vector<double>	xmin;
	double			fmin;
	double			lb[D];
	double			ub[D];
	int				maxfunevals = 3e5;

	for (int i = 0; i < D; ++i)
	{
		lb[i] = -100;
		ub[i] = 100;
	}
	
	double sum_solutionerror = 0;
	for (int t = 0; t < T; ++t)
	{
		derand1bin(xmin, fmin, lb, ub, maxfunevals, D);
		solutionerror[t] = fmin;
		sum_solutionerror += solutionerror[t];
	}

	cout << "DE/rand/1/bin" << endl;
	cout << "Mean: " << (sum_solutionerror / T) << endl;

	sum_solutionerror = 0;
	for (int t = 0; t < T; ++t)
	{
		derand1eig(xmin, fmin, lb, ub, maxfunevals, D);
		solutionerror[t] = fmin;
		sum_solutionerror += solutionerror[t];
	}

	cout << "DE/rand/1/eig" << endl;
	cout << "Mean: " << (sum_solutionerror / T) << endl;
	system("pause");
	return 0;
}

