package deeig;

import org.apache.commons.math3.linear.Array2DRowRealMatrix;
import org.apache.commons.math3.linear.EigenDecomposition;
import org.apache.commons.math3.linear.RealMatrix;

public class Xover {

	public static void run(double[][] U, double[][] X, double[][] V,
			double[] CR, int D, double P, int NP) {

		// Covariance matrix (12)
		double[][] C = new double[D][D];
		double[] m = new double[D];

		for (int j = 0; j < D; ++j) {
			m[j] = X[0][j];
		}

		for (int i = 1; i < NP; ++i) {
			for (int j = 0; j < D; ++j) {
				m[j] += X[i][j];
			}
		}

		for (int i = 0; i < D; ++i) {
			m[i] /= NP;
		}
		
		for (int i = 0; i < D; ++i) {
			for (int j = 0; j < D; ++j) {
				C[i][j] = 0;
				for (int k = 0; k < NP; ++k) {
					C[i][j] += (X[k][i] - m[i]) * (X[k][j] - m[j]);
				}
				C[i][j] /= (NP - 1);
			}
		}
		
		// Eigendecomposition (14)
		RealMatrix RM_C = new Array2DRowRealMatrix(C);
		RealMatrix RM_Q = new EigenDecomposition(RM_C).getV();
		double[][] Q = RM_Q.getData();
		
		// Crossover (16)
		for (int i = 0; i < NP; ++i) {
			Mixcrossover.run(U[i], X[i], V[i], CR[i], D, Q, NP);			
		}
	}
}
