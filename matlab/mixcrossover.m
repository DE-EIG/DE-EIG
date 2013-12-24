function u = mixcrossover(x, v, u, CR, D, Q, P)
%MIXCROSSOVER Mix the binomial and 'EIG' crossover (16)

if rand < P
	u = eigcrossover(x, v, u, CR, D, Q);
else
	u = bincrossover(x, v, u, CR, D);
end
end
