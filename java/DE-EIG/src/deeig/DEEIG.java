package deeig;

public class DEEIG {

	public static void main(String[] args) {
		final int D = 30;
		final int T = 50;
		double[] solutionerror = new double[T];
		double[] lb = new double[D];
		double[] ub = new double[D];
		int maxfunevals = (int) 3e5;

		for (int i = 0; i < D; ++i) {
			lb[i] = -100;
			ub[i] = 100;
		}

		double sum_solutionerror = 0;
		DErand1bin derand1bin = new DErand1bin();
		for (int t = 0; t < T; ++t) {
			derand1bin.run(lb, ub, maxfunevals);
			solutionerror[t] = derand1bin.getFmin();
			sum_solutionerror += solutionerror[t];
		}

		System.out.println("DE/rand/1/bin");
		System.out.println("Mean: " + (sum_solutionerror / T));

		sum_solutionerror = 0;
		DErand1eig derand1eig = new DErand1eig();
		for (int t = 0; t < T; ++t) {
			derand1eig.run(lb, ub, maxfunevals);
			solutionerror[t] = derand1eig.getFmin();
			sum_solutionerror += solutionerror[t];
		}
		
		System.out.println("DE/rand/1/eig");
		System.out.println("Mean: " + (sum_solutionerror / T));
	}

}
