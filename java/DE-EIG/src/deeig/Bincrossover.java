package deeig;

public class Bincrossover {

	public static void run(double[] u, double[] x, double[] v, double CR, int D) {
		// Binomial Crossover (10)
		int jrand = (int) Math.floor(Math.random() * D);
		for (int j = 0; j < D; ++j) {
			if (Math.random() < CR || j == jrand) {
				u[j] = v[j];
			} else {
				u[j] = x[j];
			}
		}
	}
}
