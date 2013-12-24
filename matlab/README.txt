HOW TO INTEGRATE DE-EIG INTO YOUR DE VARIANTS:

	Simply call xover.m to complete the crossover. Please note that the 
	input parameter CR must be a NPx1 vector which contains the crossover 
	rate for each pair of target vector and donor vector.

TO THINK ABOUT THE BIG PICTURE OF DE-EIG:

	Please run this program by run.m.

LIST OF FUNCTIONS:

Entry point of the program:     run.m
Test function:                  ellipsoidalrot.m
DE/rand/1/bin:                  derand1bin.m
DE/rand/1/eig:                  derand1eig.m
Binomial crossover:             bincrossover.m
EIG crossover:                  eigcrossover.m
Mixed bin and EIG crossover:    mixcrossover.m
Overall crossover:              xover.m

DEVELOPMENT ENVIRONMENT:

MATLAB(R)
R2012b (8.0.0.783)
64-bit (win64)
