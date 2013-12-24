package deeig;

public class DErand1eig {
	
	private double[] xmin;
	private double fmin;

	public void run(double[] lb, double[] ub, int maxfunevals) {

		// Algorithmic parameters
		final int D = lb.length;
		final int NP = 5 * D;
		final double F = 0.7;
		final double P = 0.5;
		double[] CR = new double[NP];

		for (int i = 0; i < NP; ++i) {
			CR[i] = 0.5;
		}

		// Initialize population (4)
		double[][] X = new double[NP][D];
		for (int i = 0; i < NP; ++i) {
			for (int j = 0; j < D; ++j) {
				X[i][j] = lb[j] + (ub[j] - lb[j]) * Math.random();
			}
		}

		// Initialize variables
		double[][] V = new double[NP][D];
		double[][] U = new double[NP][D];

		// Evaluation
		int counteval = 0;
		double[] f = new double[NP];
		for (int i = 0; i < NP; ++i) {
			f[i] = Ellipsoidalrot.evaluate(X[i]);
		}
		counteval += NP;

		while (counteval <= maxfunevals - NP) {
			// Mutation (5)
			for (int i = 0; i < NP; ++i) {
				int r1 = (int) Math.floor(Math.random() * NP);
				int r2 = (int) Math.floor(Math.random() * NP);
				int r3 = (int) Math.floor(Math.random() * NP);
				while (r2 == r3) {
					r3 = (int) Math.floor(Math.random() * NP);
				}
				for (int j = 0; j < D; ++j) {
					V[i][j] = X[r1][j] + F * (X[r2][j] - X[r3][j]);
				}
			}

			// Crossover (16)
			Xover.run(U, X, V, CR, D, P, NP);

			// Selection (11)
			for (int i = 0; i < NP; ++i) {
				double fui = Ellipsoidalrot.evaluate(U[i]);
				if (fui < f[i]) {
					f[i] = fui;
					for (int j = 0; j < D; ++j) {
						X[i][j] = U[i][j];
					}
				}
			}
			counteval += NP;
		}

		int fminidx = 0;
		fmin = f[0];
		for (int i = 1; i < NP; ++i) {
			if (f[i] < fmin) {
				fmin = f[i];
				fminidx = i;
			}
		}
		xmin = X[fminidx];
	}

	public double[] getXmin() {
		return xmin;
	}

	public double getFmin() {
		return fmin;
	}
}
