package deeig;

public class Mixcrossover {

	public static void run(double[] u, double[] x, double[] v, double CR,
			int D, double[][] Q, double P) {
		
		// Mix crossover (16)
		if (Math.random() < P) {
			Eigcrossover.run(u, x, v, CR, D, Q);
		} else {
			Bincrossover.run(u, x, v, CR, D);
		}

	}
}
