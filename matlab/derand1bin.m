function [xmin, fmin] = derand1bin(fitfun, lb, ub, maxfunevals)
% Algorithmic parameters
D	= numel(lb);
NP	= 5 * D;
F	= 0.7;
CR	= 0.5;

% Initialize population (4)
X = zeros(D, NP);
for i = 1 : NP
	X(:, i) = lb + (ub - lb) .* rand(D, 1);
end

% Initialize variables
V = X;
U = X;

% Evaluation
counteval = 0;
f = zeros(1, NP);
for i = 1 : NP
	f(i) = feval(fitfun, X(:, i));
end
counteval = counteval + NP;

while counteval <= maxfunevals - NP	
	% Mutation (5)
	for i = 1 : NP
		r1 = floor(1 + NP * rand);
		r2 = floor(1 + NP * rand);
		r3 = r2;		
		while r2 == r3
			r3 = floor(1 + NP * rand);
		end
		V(:, i) = X(:, r1) + F * (X(:, r2) - X(:, r3));
	end
	
	% Crossover (10)
	for i = 1 : NP
		U(:, i) = bincrossover(X(:, i), V(:, i), U(:, i), CR, D);
	end
	
	% Selection	(11)
	for i = 1 : NP
		fui = feval(fitfun, U(:, i));
		counteval = counteval + 1;
		
		if fui < f(i)
			f(i) = fui;
			X(:, i) = U(:, i);
		end
	end
end

[fmin, fminidx] = min(f);
xmin = X(:, fminidx);
end