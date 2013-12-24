function u = bincrossover(x, v, u, CR, D)
% BINCROSSOVER Binomial Crossover (10)
jrand = floor(1 + D * rand);
for i = 1 : D
	if rand < CR || i == jrand
		u(i) = v(i);
	else
		u(i) = x(i);
	end
end
end
