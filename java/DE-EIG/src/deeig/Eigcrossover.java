package deeig;

public class Eigcrossover {

	public static void run(double[] u, double[] x, double[] v, double CR,
			int D, double[][] Q) {
		// Eigenvector-based crossover (15)
		double[] ut = new double[D];
		double[] xt = new double[D];
		double[] vt = new double[D];

		for (int j = 0; j < D; ++j) {
			xt[j] = 0;
			vt[j] = 0;
			for (int k = 0; k < D; ++k) {
				xt[j] += Q[k][j] * x[k];
				vt[j] += Q[k][j] * v[k];
			}
		}

		int jrand = (int) Math.floor(Math.random() * D);
		for (int j = 0; j < D; ++j) {
			if (Math.random() < CR || j == jrand) {
				ut[j] = vt[j];
			} else {
				ut[j] = xt[j];
			}
		}

		for (int j = 0; j < D; ++j) {
			u[j] = 0;
			for (int k = 0; k < D; ++k) {
				u[j] += Q[j][k] * ut[k];
			}
		}
	}
}
