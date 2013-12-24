#pragma once
#include "stdafx.h"
using std::vector;
double ellipsoidalrot(double x[]);
void derand1bin(vector<double> &xmin, double &fmin, double lb[], double ub[], int maxfunevals, int D);
void derand1eig(vector<double> &xmin, double &fmin, double lb[], double ub[], int maxfunevals, int D);
void bincrossover(
	vector<double> &u, 
	const vector<double> &x, 
	const vector<double> &v, 
	const double CR, 
	const int D);
void eigcrossover(
	vector<double> &u, 
	const vector<double> &x, 
	const vector<double> &v, 
	const double CR, 
	const int D, 
	const vector<vector<double>> &Q);
void mixcrossover(
	vector<double> &u, 
	const vector<double> &x, 
	const vector<double> &v, 
	const double CR, 
	const int D, 
	const vector<vector<double>> &Q,
	const double P);
void xover(
	vector<vector<double>> &U, 
	const vector<vector<double>> &X, 
	const vector<vector<double>> &V,
	const vector<double> &CR,
	const int D,
	const double P,
	const int NP);
void Eigen(int N, vector<vector<double>> C, double *diag, vector<vector<double>> &Q, double *rgtmp);
void QLalgo2 (int n, double *d, double *e, vector<vector<double>> &V);
void Householder2(int n, vector<vector<double>> &V, double *d, double *e);
double myhypot(double a, double b);