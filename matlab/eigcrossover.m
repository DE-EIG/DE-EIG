function u = eigcrossover(x, v, u, CR, D, Q)
% EIGCROSSOVER Eigenvector-based crossover (15)
ut = u;
xt = Q' * x;
vt = Q' * v;
jrand = floor(1 + D * rand);

for j = 1 : D
	if rand < CR || j == jrand
		ut(j) = vt(j);
	else
		ut(j) = xt(j);
	end
end

u = Q * ut;
end
