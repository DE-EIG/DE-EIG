#include "stdafx.h"
using std::vector;

void derand1eig(vector<double> &xmin, double &fmin, double lb[], double ub[], int maxfunevals, int D)
{
	// Algorithmic parameters
	int		NP	= 5 * D;
	double	F	= 0.7;
	double	P	= 0.5;
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
	
	vector<vector<double>>	V	= X;
	vector<vector<double>>	U	= X;
	
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
		
		// Crossover (16)
		xover(U, X, V, CR, D, P, NP);

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

void Eigen(int N, vector<vector<double>> C, double *diag, vector<vector<double>> &Q, double *rgtmp)
/* 
   Calculating eigenvalues and vectors. 
   Input: 
     N: dimension.
     C: symmetric (1:N)xN-matrix, solely used to copy data to Q
     niter: number of maximal iterations for QL-Algorithm. 
     rgtmp: N+1-dimensional vector for temporal use. 
   Output: 
     diag: N eigenvalues. 
     Q: Columns are normalized eigenvectors.

   Code adapted from CMA-ES source code (C ANSI). 
 */
{
  int i, j;

  /* copy C to Q */
  if (C != Q) {
    for (i=0; i < N; ++i)
      for (j = 0; j <= i; ++j)
        Q[i][j] = Q[j][i] = C[i][j];
  }

#if 0
    Householder( N, Q, diag, rgtmp);
    QLalgo( N, diag, Q, 30*N, rgtmp+1);
#else
    Householder2(N, Q, diag, rgtmp);
    QLalgo2(N, diag, rgtmp, Q);
#endif

}  

void QLalgo2 (int n, double *d, double *e, vector<vector<double>> &V) {
  /*
    -> n     : Dimension. 
    -> d     : Diagonale of tridiagonal matrix. 
    -> e[1..n-1] : off-diagonal, output from Householder
    -> V     : matrix output von Householder
    <- d     : eigenvalues
    <- e     : garbage?
    <- V     : basis of eigenvectors, according to d

    Symmetric tridiagonal QL algorithm, iterative 
    Computes the eigensystem from a tridiagonal matrix in roughtly 3N^3 operations
    
    code adapted from Java JAMA package, function tql2. 	
    Code adapted from CMA-ES source code (C ANSI). 
  */

  int i, k, l, m;
  double f = 0.0;
  double tst1 = 0.0;
  double eps = 2.22e-16; /* Math.pow(2.0,-52.0);  == 2.22e-16 */
  
      /* shift input e */
      for (i = 1; i < n; i++) {
         e[i-1] = e[i];
      }
      e[n-1] = 0.0; /* never changed again */
   
      for (l = 0; l < n; l++) { 

        /* Find small subdiagonal element */
   
         if (tst1 < fabs(d[l]) + fabs(e[l]))
           tst1 = fabs(d[l]) + fabs(e[l]);
         m = l;
         while (m < n) {
           if (fabs(e[m]) <= eps*tst1) {
             /* if (fabs(e[m]) + fabs(d[m]+d[m+1]) == fabs(d[m]+d[m+1])) { */
               break;
            }
            m++;
         }
   
         /* If m == l, d[l] is an eigenvalue, */
         /* otherwise, iterate. */
   
         if (m > l) {  /* TODO: check the case m == n, should be rejected here!? */
            int iter = 0;
            do { /* while (fabs(e[l]) > eps*tst1); */
               double dl1, h;
               double g = d[l];
               double p = (d[l+1] - g) / (2.0 * e[l]); 
               double r = myhypot(p, 1.); 

               iter = iter + 1;  /* Could check iteration count here */
   
               /* Compute implicit shift */
   
               if (p < 0) {
                  r = -r;
               }
               d[l] = e[l] / (p + r);
               d[l+1] = e[l] * (p + r);
               dl1 = d[l+1];
               h = g - d[l];
               for (i = l+2; i < n; i++) {
                  d[i] -= h;
               }
               f = f + h;
   
               /* Implicit QL transformation. */
   
               p = d[m];
             {
               double c = 1.0;
               double c2 = c;
               double c3 = c;
               double el1 = e[l+1];
               double s = 0.0;
               double s2 = 0.0;
               for (i = m-1; i >= l; i--) {
                  c3 = c2;
                  c2 = c;
                  s2 = s;
                  g = c * e[i];
                  h = c * p;
                  r = myhypot(p, e[i]);
                  e[i+1] = s * r;
                  s = e[i] / r;
                  c = p / r;
                  p = c * d[i] - s * g;
                  d[i+1] = h + s * (c * g + s * d[i]);
   
                  /* Accumulate transformation. */
   
                  for (k = 0; k < n; k++) {
                     h = V[k][i+1];
                     V[k][i+1] = s * V[k][i] + c * h;
                     V[k][i] = c * V[k][i] - s * h;
                  }
               }
               p = -s * s2 * c3 * el1 * e[l] / dl1;
               e[l] = s * p;
               d[l] = c * p;
             }
   
               /* Check for convergence. */
   
            } while (fabs(e[l]) > eps*tst1);
         }
         d[l] = d[l] + f;
         e[l] = 0.0;
      }
     
      /* Sort eigenvalues and corresponding vectors. */
#if 1
      /* TODO: really needed here? So far not, but practical and only O(n^2) */
      {
      int j; 
      double p;
      for (i = 0; i < n-1; i++) {
         k = i;
         p = d[i];
         for (j = i+1; j < n; j++) {
            if (d[j] < p) {
               k = j;
               p = d[j];
            }
         }
         if (k != i) {
            d[k] = d[i];
            d[i] = p;
            for (j = 0; j < n; j++) {
               p = V[j][i];
               V[j][i] = V[j][k];
               V[j][k] = p;
            }
         }
      }
      }
#endif 
} /* QLalgo2 */ 


/* ========================================================= */
void Householder2(int n, vector<vector<double>> &V, double *d, double *e) {
  /* 
     Householder transformation of a symmetric matrix V into tridiagonal form. 
   -> n             : dimension
   -> V             : symmetric nxn-matrix
   <- V             : orthogonal transformation matrix:
                      tridiag matrix == V * V_in * V^t
   <- d             : diagonal
   <- e[0..n-1]     : off diagonal (elements 1..n-1) 

   code slightly adapted from the Java JAMA package, function private tred2()  
   Code adapted from CMA-ES source code (C ANSI). 
  */

  int i,j,k; 

      for (j = 0; j < n; j++) {
         d[j] = V[n-1][j];
      }

      /* Householder reduction to tridiagonal form */
   
      for (i = n-1; i > 0; i--) {
   
        /* Scale to avoid under/overflow */
   
         double scale = 0.0;
         double h = 0.0;
         for (k = 0; k < i; k++) {
            scale = scale + fabs(d[k]);
         }
         if (scale == 0.0) {
            e[i] = d[i-1];
            for (j = 0; j < i; j++) {
               d[j] = V[i-1][j];
               V[i][j] = 0.0;
               V[j][i] = 0.0;
            }
         } else {
   
           /* Generate Householder vector */

            double f, g, hh;
   
            for (k = 0; k < i; k++) {
               d[k] /= scale;
               h += d[k] * d[k];
            }
            f = d[i-1];
            g = sqrt(h);
            if (f > 0) {
               g = -g;
            }
            e[i] = scale * g;
            h = h - f * g;
            d[i-1] = f - g;
            for (j = 0; j < i; j++) {
               e[j] = 0.0;
            }
   
            /* Apply similarity transformation to remaining columns */
   
            for (j = 0; j < i; j++) {
               f = d[j];
               V[j][i] = f;
               g = e[j] + V[j][j] * f;
               for (k = j+1; k <= i-1; k++) {
                  g += V[k][j] * d[k];
                  e[k] += V[k][j] * f;
               }
               e[j] = g;
            }
            f = 0.0;
            for (j = 0; j < i; j++) {
               e[j] /= h;
               f += e[j] * d[j];
            }
            hh = f / (h + h);
            for (j = 0; j < i; j++) {
               e[j] -= hh * d[j];
            }
            for (j = 0; j < i; j++) {
               f = d[j];
               g = e[j];
               for (k = j; k <= i-1; k++) {
                  V[k][j] -= (f * e[k] + g * d[k]);
               }
               d[j] = V[i-1][j];
               V[i][j] = 0.0;
            }
         }
         d[i] = h;
      }
   
      /* Accumulate transformations */
   
      for (i = 0; i < n-1; i++) {
         double h; 
         V[n-1][i] = V[i][i];
         V[i][i] = 1.0;
         h = d[i+1];
         if (h != 0.0) {
            for (k = 0; k <= i; k++) {
               d[k] = V[k][i+1] / h;
            }
            for (j = 0; j <= i; j++) {
               double g = 0.0;
               for (k = 0; k <= i; k++) {
                  g += V[k][i+1] * V[k][j];
               }
               for (k = 0; k <= i; k++) {
                  V[k][j] -= g * d[k];
               }
            }
         }
         for (k = 0; k <= i; k++) {
            V[k][i+1] = 0.0;
         }
      }
      for (j = 0; j < n; j++) {
         d[j] = V[n-1][j];
         V[n-1][j] = 0.0;
      }
      V[n-1][n-1] = 1.0;
      e[0] = 0.0;

} /* Housholder() */

double myhypot(double a, double b) 
/* sqrt(a^2 + b^2) numerically stable. 

   Code adapted from CMA-ES source code (C ANSI). 
*/
{
  double r = 0;
  if (fabs(a) > fabs(b)) {
    r = b/a;
    r = fabs(a)*sqrt(1+r*r);
  } else if (b != 0) {
    r = a/b;
    r = fabs(b)*sqrt(1+r*r);
  }
  return r;
}