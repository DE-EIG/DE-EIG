T = 50;
solutionerror = zeros(T, 1);
fitfun = 'ellipsoidalrot';
lb = -100 * ones(30, 1);
ub = 100 * ones(30, 1);
maxfunevals = 3e5;

for t = 1 : T
	[xmin, fmin] = derand1bin(fitfun, lb, ub, maxfunevals);
	solutionerror(t) = fmin;
end

fprintf('DE/rand/1/bin\n');
fprintf('Mean: %.2E\n', mean(solutionerror));
fprintf('St. D.: %.2E\n', std(solutionerror));
fprintf('--\n');

for t = 1 : T
	[xmin, fmin] = derand1eig(fitfun, lb, ub, maxfunevals);
	solutionerror(t) = fmin;
end

fprintf('DE/rand/1/eig\n');
fprintf('Mean: %.2E\n', mean(solutionerror));
fprintf('St. D.: %.2E\n', std(solutionerror));
fprintf('--\n');