HOW TO INTEGRATE DE-EIG INTO YOUR DE VARIANTS:

	Simply call xover to complete the crossover. Please note that the 
	input parameter CR must be a NPx1 vector which contains the crossover 
	rate for each pair of target vector and donor vector.

TO THINK ABOUT THE BIG PICTURE OF DE-EIG:

	Please run this program by _tmain.

LIST OF FUNCTIONS:

Entry point of the program:		DE-EIG.cpp
Test function:				ellipsoidalrot.cpp
DE/rand/1/bin:				derand1bin.cpp
DE/rand/1/eig:				derand1eig.cpp
Binomial crossover:			bincrossover.cpp
EIG crossover:				eigcrossover.cpp
Mixed bin and EIG crossover:		mixcrossover.cpp
Overall crossover:			xover.cpp

DEVELOPMENT ENVIRONMENT:

Microsoft Visual Studio 2010
ver. 10.0.40219.1 SP1Rel
